/* Author: Christoph Lassner. */
#ifndef FERTILIZED_FEATURE_EXTRACTION_DNNFEATURE_EXTRACTOR_H_
#define FERTILIZED_FEATURE_EXTRACTION_DNNFEATURE_EXTRACTOR_H_

#ifdef CAFFE_FEATURE_EXTRACTION_ENABLED
#include "../global.h"
#include "../ndarray.h"

#include <memory>
#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

namespace fertilized {

  /**
   * Extracts DNN features using a pretrained caffe network.
   *
   * Dropout layers! Mean image!
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   *
   * -----
   */
  class DNNFeatureExtractor {
   public:
    /**
     * Standard constructor.
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
     */
    DllExport DNNFeatureExtractor(const bool &use_cpu=false,
                                  const int &device_id=0,
                                  std::string net_layout_file="",
                                  std::string net_weights_file="",
                                  std::string net_outlayer="",
                                  const bool &load_mean=true,
                                  std::string mean_file="");
    DllExport ~DNNFeatureExtractor();

    /**
     * Extract DNN features with this extractor.
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
     */
    DllExport Array<float, 4, 4> extract(
      const std::vector<Array<const float, 3, 3>> &images,
      const bool &subtract_mean=true);

   private:
    void *net_ptr;
    // TODO: remove
    std::string net_outlayer;
    //caffe::Blob<float> *caffe_input;
    //std::vector<caffe::Blob<float>*> caffe_in;
    // endremove
    cv::Size input_size;
    cv::Mat mean_data;
    bool mean_available;
    int read_layer_idx;
  };

};  // namespace fertilized
#endif // CAFFE_FEATURE_EXTRACTION_ENABLED
#endif // FERTILIZED_FEATURE_EXTRACTION_DNNFEATURE_EXTRACTOR_H_
