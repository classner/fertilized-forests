/* Author: Christian Diller. */
#pragma once
#ifndef FERTILIZED_LEAFS_BOOSTINGLEAFMANAGER_H_
#define FERTILIZED_LEAFS_BOOSTINGLEAFMANAGER_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#ifdef DEBUG_MESSAGES
#include <iostream>
#endif
#include <numeric>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>

#include "../global.h"
#include "../types.h"
#include "../data_providers/idataprovider.h"
#include "../features/isurfacecalculator.h"
#include "./ileafmanager.h"
#include "./classificationleafmanager.h"

namespace fertilized {
  /**
   * \brief Allows the boosting strategies to set their own tree functions
   * to influence the combined result.
   *
   * Using thes LeafManager may lead to better classifcation results.
   *
   * Note that the output does not represent probabilites and may vary when
   * using different \ref IBoostingStrategies
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
   * - int; uint
   * - float; uint
   * - double; uint
   * - uint8_t; uint
   * - uint8_t; int16_t
   * .
   * Serialization generation: 101
   *
   * -----
   */
  template <typename input_dtype, typename annotation_dtype>
  class BoostingLeafManager : public ClassificationLeafManager<input_dtype, annotation_dtype> {
   public:
    typedef ClassificationLeafManager<input_dtype, annotation_dtype> leaf_man_t;
    using typename leaf_man_t::dprov_t;
    using typename leaf_man_t::wlresult_list_t;

    /**
    * -----
    * Available in:
    * - C++
    * - Python
    * - Matlab
    * .
    *
    * -----
    *
    * \param n_classes uint>1
    *   The number of classes.
    */
    explicit BoostingLeafManager(const uint &n_classes)
      : n_classes(n_classes),
        ClassificationLeafManager<input_dtype, annotation_dtype>(n_classes) {}

    /** Gets the results weighted by the given weight functions. */
    std::vector<float> get_combined_result(const wlresult_list_t &leaf_results) {
        std::vector<float> combined_result(n_classes);
        for (size_t resultindex = 0; resultindex < leaf_results.size(); ++resultindex) {
            if (weight_functions.find(resultindex) == weight_functions.end()) {
                throw Fertilized_Exception("Boosting leaf manager needs one "
                                           "weight function per tree");
            } else {
                // Let the weight function calculate the result vector and add
                // the elements to combined_results
                std::vector<float> results = weight_functions[resultindex](
                    leaf_results[resultindex].first);
                for (size_t binindex = 0; binindex < static_cast<size_t>(n_classes); ++binindex) {
                    combined_result[binindex] += results[binindex];
                }
            }
        }
        return combined_result;
    }

    /** Set a weight function */
    void set_weight_function(size_t tree_id,
                             std::function<
                               std::vector<float>(std::vector<float>)> function) {
        weight_functions[tree_id] = function;
    }

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
                                 annotation_dtype,
                                 std::vector<float>,
                                 std::vector<float>> &rhs) const {
      const auto *rhs_c = dynamic_cast<
        BoostingLeafManager<input_dtype,annotation_dtype> const*>(&rhs);
      if (rhs_c == nullptr)
        return false;
      else
        return n_classes == rhs_c -> n_classes &&
               weight_functions.size() == rhs_c -> weight_functions.size();
    };

    /** Gets the number of classes. */
    unsigned int get_n_classes() const {
      return n_classes;
    }

#ifdef SERIALIZATION_ENABLED
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      ar & boost::serialization::base_object<leaf_man_t>(*this);
      ar & n_classes;
    }
#endif

   protected:
    BoostingLeafManager() {}

   private:
    uint n_classes;
    std::map<size_t,
      std::function<std::vector<float>(std::vector<float>)>> weight_functions;
  };

};  // namespace fertilized
#endif  // FERTILIZED_LEAFS_BOOSTINGLEAFMANAGER_H_
