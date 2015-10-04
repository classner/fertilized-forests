/* Author: Moritz Einfalt, Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_LEAFS_REGRESSIONLEAFMANAGER_H_
#define FERTILIZED_LEAFS_REGRESSIONLEAFMANAGER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <numeric>
#include <unordered_map>
#include <vector>
#include <mutex>

#include "../global.h"
#include "../types.h"
#include "../data_providers/idataprovider.h"
#include "../features/isurfacecalculator.h"
#include "../features/ifeatureselectionprovider.h"
#include "../impurities/ientropyfunction.h"
#include "../regression/iregressioncalculator.h"
#include "../regression/constantregressioncalculator.h"
#include "../util/checks.h"
#include "./ileafmanager.h"

namespace fertilized {
  /**
   * \brief Manages the leaf nodes of regression trees.
   *
   * This leaf manager creates leaf nodes and stores a probabilistic regression
   * model at each leaf.
   *
   * \ingroup fertilizedleafsGroup
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - float
   * - double
   * .
   *
   * -----
   */
  template <typename input_dtype>
  class RegressionLeafManager
    : public ILeafManager<input_dtype, input_dtype, std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,std::shared_ptr<std::vector<input_dtype>>>,float>>> {
   public:
    typedef ILeafManager<input_dtype, input_dtype,
                         std::pair<std::shared_ptr<std::vector<input_dtype>>,
                                   std::shared_ptr<std::vector<input_dtype>>>,
                         std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,
                                               std::shared_ptr<std::vector<input_dtype>>>,float>> >
                         leaf_man_t;
    using typename leaf_man_t::dprov_t;
    using typename leaf_man_t::wlresult_list_t;

    typedef IRegressionCalculator<input_dtype> IRegressionCalculator_t;
    typedef Eigen::Matrix<input_dtype, Eigen::Dynamic, Eigen::Dynamic,
      Eigen::RowMajor, Eigen::Dynamic, Eigen::Dynamic> Matrix_regression_t;
    typedef Eigen::Matrix<input_dtype, Eigen::Dynamic, 1,
      Eigen::ColMajor, Eigen::Dynamic, 1> Vector_regression_t;

    typedef std::tuple<std::vector<size_t>, FeatCalcParamSet,
      EThresholdSelection, std::pair<int16_t, int16_t>>
      decision_tuple_t;

    typedef std::pair<std::shared_ptr<IRegressionCalculator_t>,
                      std::vector<size_t>> regression_result_t;


    /**
     * \brief Constructor for a RegressionLeafManager
     *
     * Costructs a RegressionLeafManager.
     * For each leaf, a number of dimension selections used as regressors is asessed.
     * The selection resulting in the regression model with the lowest entropy is used.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param selection_provider ISelectionProvider
     *   Selection provider creating random feature selections.
     *   It specifies, how many regressors are used.
     * \param n_valids_to_use size_t>0
     *   How many valid selections are asessed, until the selection process is
     *   stopped.
     * \param regression_calculator IRegressionCalculator
     *   The regression calculator that is used to generate a regression model for each leaf.
     * \param entropy_function IEntropyFunction
     *   The entropy function used to evaluate the regression models.
     * \param use_fallback_constant_regression bool
     *   When no valid dimension selections can be found and this flag is set to true,
     *   a ConstantRegressionCalculator (independent from regressor selections) is used instead.
     *   Otherwise, this case results in a runtime exception. Default: false.
     * \param num_threads int>0
     *   The number of threads used when evaluating different selections.
     *   Default: 1.
     * \param summary_mode uint<3
     *   Determines the meaning of the values in the 2D prediction matrix of
     *   a forest (the output of the convenience `predict` method of a forest).
     *   Case 0: Each row contains the prediction for each regressor (the first
     *           half of its entries) and the expected variances for each
     *           regressor (second half of its entries). To estimate the joint
     *           variance, a gaussian is fitted over the multimodal distribution
     *           defined by all trees.
     *   Case 1: Each row contains the prediction for each regressor (the first
     *           half of its entries) and the mean of the expected variances of
     *           each tree. This has no direct semantic meaning, but can give
     *           better results in active learning applications.
     *   Case 2: Each row contains the prediction for each regressor and
     *           the variance estimate for each regressor for each tree, e.g.,
     *           (r11, r12, v11, v12, r21, r22, v21, v22, ...), with `r` and `v`
     *           denoting regressor prediction and variance respectively, the
     *           first index the tree and the second index the regressor index.
     * \returns A new RegressionLeafManager.
     */
    explicit RegressionLeafManager(const std::shared_ptr<IFeatureSelectionProvider> &selection_provider,
                                   const size_t &n_valids_to_use,
                                   const std::shared_ptr<IRegressionCalculator<input_dtype>> & regression_calculator,
                                   const std::shared_ptr<IEntropyFunction<float>> &entropy_function,
                                   const bool &use_fallback_constant_regression=false,
                                   const int &num_threads=1,
                                   const uint &summary_mode=0)
    :n_valids_to_use(n_valids_to_use),
     selection_provider(selection_provider),
     reg_calc_template(regression_calculator),
     entropy_function(entropy_function),
     use_fallback_reg_calc(use_fallback_constant_regression),
     num_threads(num_threads),
     leaf_regression_map(std::unordered_map<node_id_t, regression_result_t>()),
     summary_mode(summary_mode) {
      static_assert(std::is_floating_point<input_dtype>::value,
        "Regression datatype must be floating point.");

      if (num_threads <= 0) {
        throw Fertilized_Exception("The number of threads must be >0!");
      }
      if (n_valids_to_use == 0) {
        throw Fertilized_Exception("The number of valid features must be >0!");
      }
#ifndef _OPENMP
      if (num_threads > 1) {
        throw Fertilized_Exception("This executable has been built without "
          "OpenMP support. The number of threads must =1!");
      }
#endif
      if (summary_mode > 2) {
        throw Fertilized_Exception("Unknown summary mode (supported: 0,1,2)!");
      }
    };

    /**
     * Creates a regression leaf.
     */
    void make_leaf(
        const node_id_t &node_id,
        const elem_id_vec_t &element_list,
        const dprov_t &data_provider) {
      FASSERT(element_list.size() > 0);
      size_t n_samples = element_list.size();
      size_t input_dim = data_provider.get_feat_vec_dim();
      size_t annot_dim = data_provider.get_annot_vec_dim();
      // create the annotation matrix
      auto sample_list = data_provider.get_samples();
      auto annot_mat = std::make_shared<Matrix_regression_t>(n_samples, annot_dim);
      const input_dtype *annot_ptr;
      for (int row = 0; row < n_samples; row++) {
        annot_ptr = (*sample_list)[ element_list[row] ].annotation;
        for (int col = 0; col < annot_dim; col++) {
          (*annot_mat)(row,col) = *(annot_ptr);
          annot_ptr ++;
        }
      }
      regression_result_t best_regression_result;
      bool needs_feature_selection = reg_calc_template->needs_input_data();
      bool valid_feature_found = false;
      if (needs_feature_selection) {
        // Iterate over all feature selections
        auto suggested_feature_sets = (* selection_provider).get_proposal_generator();
        FASSERT(suggested_feature_sets -> available());
        float best_entropy = std::numeric_limits<float>::infinity();

        size_t processed_val_count = 0;
        size_t processed_val_max = (n_valids_to_use > 0 ? n_valids_to_use :
                                      suggested_feature_sets -> max_count());
        size_t processed_total = 0;

         /**
         * \brief Required to guarantee equivalent parallel results.
         * The maximum operation alone is not equivalent in serial and parallel
         * versions, since the first configuration with the best value is used.
         * It can be guaranteed if additional to the value also the loop index
         * is used.
         */
        int best_config_index = static_cast<int>(suggested_feature_sets -> max_count() + 1);
        int suggestion_index = 0;
        // TODO(Christoph): Remove locks in non-parallel mode to improve perf.?
        std::mutex mutex_track;
        std::mutex mutex_opt;
#if defined(_OPENMP)
       #pragma omp parallel num_threads(num_threads) if(num_threads != 1) \
          default(none) /* Require explicit spec. */\
          shared(best_entropy, best_regression_result, best_config_index, \
          suggested_feature_sets, data_provider, element_list, \
          processed_val_count, processed_val_max, n_samples, \
          sample_list, annot_mat, mutex_track, mutex_opt, annot_dim,  \
          suggestion_index, node_id, valid_feature_found, \
          processed_total)
#endif
        {
          auto private_reg_calc = std::unique_ptr<IRegressionCalculator<input_dtype>>(
            reg_calc_template->get_descendant_copy());
          while (suggested_feature_sets -> available() &&
                 processed_val_count < processed_val_max) {
            std::vector<size_t> feature_selection_vector;
            int my_suggestion_index;
            size_t selected_input_dim;
            size_t hom_sel_input_dim;
            {
              std::lock_guard<std::mutex> lock(mutex_track);
#if defined(_OPENMP)
              #pragma omp flush(suggestion_index, processed_val_count)
#endif
              if (suggested_feature_sets -> available() &&
                  processed_val_count < processed_val_max) {
                // Assume that this run is valid.
                processed_val_count++;
                processed_total ++;
                my_suggestion_index = suggestion_index++;
                //#pragma omp flush(suggestion_index, processed_val_count)
                feature_selection_vector = suggested_feature_sets -> get_next();

              } else {
                // Set break flag here. OpenMP doesn't allow breaks in criticals.
                my_suggestion_index = -1;
              }
            }
            if (my_suggestion_index == -1)
              break;

            // Checks.
            FASSERT(check_elem_ids_ok((*sample_list).size(), element_list));
            bool feature_selection_could_be_used = false;
            // Fill the sample matrix
            selected_input_dim = feature_selection_vector.size();
            hom_sel_input_dim = selected_input_dim + 1;
            auto sample_mat = std::make_shared<Matrix_regression_t>(n_samples, hom_sel_input_dim);
            for (int row = 0; row < n_samples; row++) {
              for (int col = 0; col < hom_sel_input_dim; col++) {
                if (col < (selected_input_dim)) {
                  (*sample_mat)(row,col) = *((*sample_list)[ element_list[row] ].data +
                                             (*sample_list)[ element_list[row] ].data_step *
                                                feature_selection_vector[col]);
                } else {
                  (*sample_mat)(row,col) = static_cast<input_dtype>(1);
                }
              }
            }


            // Calculate regression output
            private_reg_calc->initialize(sample_mat, annot_mat,
               std::make_pair(0,static_cast<int>(n_samples)));
            private_reg_calc->freeze_interval();
            float entropy = 0.f;
            bool numerical_instable = false;
            feature_selection_could_be_used = private_reg_calc->has_solution();
            if (feature_selection_could_be_used) {
              // Now calculate the entropy
              auto prediction = Eigen::Matrix<input_dtype, Eigen::Dynamic,
                1, Eigen::ColMajor>(annot_dim);
              auto pred_covar_mat = Eigen::Matrix<input_dtype, Eigen::Dynamic,
                Eigen::Dynamic, Eigen::RowMajor>(annot_dim, annot_dim);
              if (private_reg_calc->has_constant_prediction_covariance()) {
                // Calculate the determinant of the prediction covariance matrix (is diagonal!).
                 private_reg_calc->get_constant_prediction_covariance(pred_covar_mat);
                 input_dtype determinant = pred_covar_mat.diagonal().prod();
                 if (determinant < 0.f) {
                   entropy = std::numeric_limits<float>::infinity();
                   numerical_instable = true;
                 } else {
                   entropy = entropy_function->differential_normal(
                     static_cast<float>(determinant),
                     static_cast<const uint>(annot_dim)) *
                     static_cast<float>(n_samples);
                 }
              } else {
                for (size_t i = 0; i < n_samples; i++) {
                  // Calculate the determinant of the prediction covariance matrix (is diagonal!).
                  private_reg_calc->predict((*sample_mat).row(i),
                    prediction, pred_covar_mat);
                  input_dtype determinant = pred_covar_mat.diagonal().prod();
                  if (determinant < 0.f) {
                    numerical_instable=true;
                    break;
                  }
                  entropy += entropy_function->differential_normal(
                    static_cast<float>(determinant),
                    static_cast<const uint>(annot_dim));
                }
              }

              if (! numerical_instable) {
                {
                  std::lock_guard<std::mutex> lock(mutex_opt);
                  if (entropy < best_entropy ||
                      entropy == best_entropy &&
                      my_suggestion_index < best_config_index) {
                    best_entropy = entropy;
                    valid_feature_found = true;
                    best_config_index = my_suggestion_index;
                    auto best_reg_calc = std::shared_ptr<
                      IRegressionCalculator<input_dtype>>(
                        private_reg_calc->get_descendant_copy());
                    best_regression_result =
                      std::make_pair(best_reg_calc, feature_selection_vector);
                  }
                }
              }

            }
            if (((! feature_selection_could_be_used) ||
                 numerical_instable) && (n_valids_to_use > 0)) {
              {
              std::lock_guard<std::mutex> lock(mutex_track);
              processed_val_count--;
#if defined(_OPENMP)
              #pragma omp flush(processed_val_count)
#endif
              }
            }
          } // END WHILE
        }

        if (valid_feature_found) {
          auto ret_val = leaf_regression_map.emplace(node_id, best_regression_result);
          if (!ret_val.second) {
            throw Fertilized_Exception("Tried to create the leaf value for a node "
              "that has already been assigned one.");
          }
        } else if(! use_fallback_reg_calc) {
          std::stringstream ss;
          ss << n_samples;
          ss << ". Selections tried: ";
          ss << processed_total;
          std::string n_samples_string = ss.str();
          throw Fertilized_Exception("Tried to create a leaf from data, from which "
            "no unique regression model can be obtained. Number of data samples: " + n_samples_string);
        }
      }

      if ((! needs_feature_selection) || ((! valid_feature_found) && use_fallback_reg_calc)) {
        std::shared_ptr<IRegressionCalculator<input_dtype>> best_reg_calc;
        if (reg_calc_template->needs_input_data())
          best_reg_calc = std::shared_ptr<IRegressionCalculator<input_dtype>>(
            new ConstantRegressionCalculator<input_dtype>());
        else
          best_reg_calc = std::shared_ptr<IRegressionCalculator<input_dtype>>(
            reg_calc_template->get_descendant_copy());

        auto sample_mat = std::make_shared<Matrix_regression_t>(1, 1);
        best_reg_calc->initialize(sample_mat, annot_mat,
          std::make_pair(0,static_cast<int>(n_samples)));
        best_reg_calc->freeze_interval();

        std::vector<size_t> empty_feat_selection = std::vector<size_t>(1);
        empty_feat_selection[0] = 0;
        best_regression_result = std::make_pair(best_reg_calc, empty_feat_selection);
        auto ret_val = leaf_regression_map.emplace(node_id, best_regression_result);
        if (!ret_val.second) {
          throw Fertilized_Exception("Tried to create the leaf value for a node "
            "that has already been assigned one.");
        }
      }



    };

    /**
     * \brief Returns true for all \ref IDataProvider s with the appropriate
     * type. It DOES NOT check whether all annotations are in the correct
     * range.
     */
    bool IsCompatibleWith(const dprov_t &data_provider) const  {
      return true;
    };

    /** \brief Returns the prediction probability distribution. */
    std::pair<std::shared_ptr<std::vector<input_dtype>>,
              std::shared_ptr<std::vector<input_dtype>>> get_result(const node_id_t &node_id,
                                                                    const input_dtype *data,
                                                                    const size_t &data_step=1,
                                                                    const std::function<void(void*)> &dptf = nullptr) const {
      // TODO Moritz: Use the transfer function, if given
      auto best_result = leaf_regression_map.at(node_id);
      auto reg_calc = best_result.first;
      size_t annot_dim = reg_calc->get_annotation_dimension();
      // prepare the output containers
      auto prediction = std::make_shared<std::vector<input_dtype>> (annot_dim);
      auto covar_mat_diag = std::make_shared<std::vector<input_dtype>> (annot_dim);
      Vector_regression_t sample_vec (1);
      if (reg_calc->needs_input_data()){
        // Use the transfer function if available
        std::vector<size_t> selected_features;
        if (dptf != nullptr) {
          /*
          // Create a decision_tuple with the selected features as the only valid data
          FeatCalcParamSet emptyParamSet();
          std::pair<int16_t,int16_t> emptyPair = std::make_pair(0,0);
          decision_tuple_t decision_tuple = std::make_tuple(std::get<3>(regression_result), emptyParamSet,
                                                           EThresholdSelection::less_only, emptyPair);
          dptf(static_cast<void*>(&decision_tuple));
          selected_features = std::get<0>(decision_tuple);
          */
          selected_features = best_result.second;
        } else {
          selected_features = best_result.second;
        }

        size_t n_selected = selected_features.size();
        // create the sample vector
        sample_vec = Vector_regression_t(n_selected + 1);
        for (int i = 0; i < n_selected + 1; i++) {
          if (i < n_selected) {
            sample_vec(i) = data [selected_features[i] * data_step];
          } else {
            sample_vec(i) = static_cast<input_dtype>(1);
          }
        }

      }
      // get the prediction mean and covariance matrix of its probability distribution
      Vector_regression_t single_prediction (annot_dim);
      Matrix_regression_t prediction_covar_mat (annot_dim, annot_dim);
      reg_calc->predict(sample_vec, single_prediction, prediction_covar_mat);
      std::move(single_prediction.data(), single_prediction.data() + annot_dim, (*prediction).begin());
      // only return the diagonal elements of the covar matrix (the others are zero)
      for (int dim = 0; dim < annot_dim; dim++) {
        (*covar_mat_diag)[dim] = prediction_covar_mat(dim,dim);
      }

      return std::make_pair (prediction, covar_mat_diag);
    };

    /** Returns the plain leaf results. */
    std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,
                          std::shared_ptr<std::vector<input_dtype>>>,float>> get_combined_result(
      const wlresult_list_t &leaf_results) {
      return leaf_results;
    };

    /**
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     */
    bool operator==(const ILeafManager<input_dtype,
                                 input_dtype,
                                 std::pair<std::shared_ptr<std::vector<input_dtype>>,
                                           std::shared_ptr<std::vector<input_dtype>>>,
                                 std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,
                                                       std::shared_ptr<std::vector<input_dtype>>>,float>> > &rhs) const {
      const auto *rhs_c = dynamic_cast<RegressionLeafManager<input_dtype> const*>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else
        return n_valids_to_use == rhs_c -> n_valids_to_use &&
               num_threads == rhs_c -> num_threads &&
               selection_provider == rhs_c -> selection_provider &&
               use_fallback_reg_calc == rhs_c -> use_fallback_reg_calc &&
               leaf_regression_map == rhs_c -> leaf_regression_map;
    };

    /** Twice the prediction dimension. */
    size_t get_summary_dimensions(const size_t &n_trees) const {
      const auto &best_result = *(leaf_regression_map.begin());
      auto reg_calc = best_result.second.first;
      size_t annot_dim = reg_calc->get_annotation_dimension();
      if (summary_mode == 2) {
        return static_cast<int>(2 * annot_dim * n_trees);
      } else {
        return static_cast<int>(2 * annot_dim);
      }
    };

    /** Returns the prediction value and the covariance values. */
    void summarize_tree_result(const std::pair<std::shared_ptr<std::vector<input_dtype>>,
                                               std::shared_ptr<std::vector<input_dtype>>> &tree_result,
                               const ArrayRef<double, 1, 1> &result_row)
      const {
      std::copy((tree_result.first) -> begin(),
                (tree_result.first) -> end(),
                result_row.getData());
      std::copy((tree_result.second) -> begin(),
                (tree_result.second) -> end(),
                result_row.getData() + tree_result.first -> size());
    };

    /** Returns the prediction value and the variance of a mixed gaussian distribution. */
    void summarize_forest_result(const std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,
                                                             std::shared_ptr<std::vector<input_dtype>>>,float>> &forest_result,
                                 const ArrayRef<double, 1, 1> &result_row)
      const {
      // Initialize the row to zeros.
      result_row.deep() = 0.;
      float weight_sum = 0.f;
      FASSERT(result_row.getNumElements() % 2 == 0);
      size_t n_elements = result_row.getNumElements() / 2;
      if (summary_mode == 2) {
        FASSERT(n_elements % forest_result.size() == 0);
        n_elements /= forest_result.size();
      }
      size_t tree_idx = 0;
      for (const auto &res_pair : forest_result) {
        float weight = res_pair.second;
        weight_sum += weight;
        const auto &value_pair = res_pair.first;
        const auto &value_vec = *(value_pair.first);
        const auto &covd_vec = *(value_pair.second);
        switch (summary_mode) {
        case 0:
          // Here, a new Gaussian distribution will be determined that spans
          // all the different models returned by the trees. This does, in
          // general, not make much sense, since the distribution can be strongly
          // multimodal. However, for this convenience interface, the value CAN
          // be helpful to determine the degree of uncertainty at this very
          // position. For the maths, see, e.g.,
          // http://stats.stackexchange.com/questions/16608/what-is-the-variance-of-the-weighted-mixture-of-two-gaussians.
          for (size_t i = 0; i < n_elements; ++i) {
            result_row[i] += value_vec[i] * weight;
            result_row[i + n_elements] += weight * (value_vec[i]*value_vec[i] + covd_vec[i]);
          }
          break;
        case 1:
          // Mean prediction, mean variances.
          for (size_t i = 0; i < n_elements; ++i) {
            result_row[i] += value_vec[i] * weight;
            result_row[i + n_elements] += covd_vec[i] * weight;
          }
          break;
        case 2:
          // All values.
          for (size_t i = 0; i < n_elements; ++i) {
            result_row[tree_idx*n_elements*2+i] = value_vec[i];
            result_row[tree_idx*n_elements*2+i+n_elements] = covd_vec[i];
          }
          tree_idx++;
          break;
        }
      }
      if (summary_mode != 2)
        result_row /= weight_sum;
      if (summary_mode == 0) {
        // The first part of the vector now contains \mu, the second \mu^{(2)}
        // (the second moment). The variance (assuming a normal distribution)
        // is then given by \mu^{(2)}-\mu^2.
        for (size_t i = 0; i < n_elements; ++i) {
          result_row[i + n_elements] -= result_row[i] * result_row[i];
        }
      }
    };

    /** Throws. */
    void add_tree_prediction_to_image(const std::pair<std::shared_ptr<std::vector<input_dtype>>,
                                                                      std::shared_ptr<std::vector<input_dtype>>> &tree_result,
                                      const Array<float, 2, 2> &result,
                                      const size_t &write_x,
                                      const size_t &write_y,
                                      const float *ratio_parameters) const {
      throw Fertilized_Exception("Cannot apply regression on an image!");
    };

    /** Throws. */
    void add_forest_prediction_to_image(
      const std::vector<float> &tree_weights,
      const std::vector<std::pair<std::pair<std::shared_ptr<std::vector<input_dtype>>,
                                  std::shared_ptr<std::vector<input_dtype>>>,float>> &forest_result,
      const Array<float, 2, 2> &result,
      const size_t &write_x,
      const size_t &write_y,
      const float *ratio_parameters) const {
      throw Fertilized_Exception("Cannot apply regression on an image!");
    };

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<leaf_man_t>(*this);
      ar & entropy_function;
      ar & reg_calc_template;
      ar & n_valids_to_use;
      ar & num_threads;
      ar & selection_provider;
      ar & use_fallback_reg_calc;
      ar & leaf_regression_map;
      ar & summary_mode;
    }
#endif

   protected:
    RegressionLeafManager() {}

   private:
    std::shared_ptr<IEntropyFunction<float>> entropy_function;
    std::shared_ptr<IRegressionCalculator<input_dtype>> reg_calc_template;
    size_t n_valids_to_use;
    int num_threads;
    std::shared_ptr<IFeatureSelectionProvider> selection_provider;
    bool use_fallback_reg_calc;
    std::unordered_map<node_id_t, regression_result_t> leaf_regression_map;
    size_t summary_mode;
 };

};  // namespace fertilized
#endif  // FERTILIZED_LEAFS_REGRESSIONLEAFMANAGER_H_
