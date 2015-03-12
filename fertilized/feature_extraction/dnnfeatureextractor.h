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
   * To obtain reproducible results, you have to remove the dropout layers
   * from the network specification file (this has been done for the default
   * AlexNet). During extraction, always the full batch size is used. This
   * means, that if you repeatedly only extract features from one image with
   * the extract method, most of the batch will be unused. You should observe
   * large speed gains by reducing the batch size in the model specification
   * file to a batch size of one in that case.
   *
   * The mean image must be subtracted from any image before
   * using the feature extractor. This can be done within the `extract` method,
   * or, if you want to use many samples from an image, you can do that before.
   * The default mean image is the one of the ImageNet dataset. The mean image
   * format is a text file with a very simple layout:
   *
   * - the first line consists of the number of rows,
   * - the second line consists of the columns,
   * - the third line consists of the number of channels,
   * - the fourth line contains all pixel values, in OpenCV memory layout
   *   (rows, columns, channels, where channels are contiguous).
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
     * \param use_cpu bool
     *    Whether to only use the CPU or use the GPU. Default: false.
     *
     * \param device_id int>=0
     *    The CUDA device id. Only relevant, if `use_cpu` is false. Default: 0.
     *
     * \param net_layout_file string
     *    The protobuf file describing the network layout. Default: "".
     *    This reserved value is resolved to the path
     *    to the AlexNet installed to the directory specified during
     *    compilation as `--caffe-model-dir`.
     *
     * \param net_weights_file string
     *    Filename of the pretrained network weights file. Default: "".
     *    This reserved value is resolved to the
     *    AlexNet weights file installed to the directory specified during
     *    compilation as `--caffe-model-dir`.
     *
     * \param net_outlayer string
     *    The name of the blob and layer from which to read. Default: "pool5".
     *
     * \param load_mean bool
     *    If set to true, loads the mean image specified by `mean_file`.
     *    Default: true.
     *
     * \param mean_file string
     *    The filename of the mean image file to use. For a file
     *    format description, see the documentation of this class. Default: "".
     *    This reserved value is resolved to the ImageNet mean file installed
     *    to the `--caffe-model-dir`.
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
     * \param images vector(Array<float, 3, 3>)
     *    This vector of C contiguous float arrays contains the images to
     *    extract the features from in OpenCV format.
     *
     * \param subtract_mean bool
     *    Whether to subtract the mean before extracting the features. Can
     *    only be used, if the mean file for this extractor has been loaded.
     *
     * \return An Array, with dimensions: n_images x n_filters x height x width.
     */
    DllExport Array<float, 4, 4> extract(
      const std::vector<Array<float, 3, 3>> &images,
      const bool &subtract_mean=true);

   private:
    void *net_ptr;
    cv::Size input_size;
    cv::Mat mean_data;
    bool mean_available;
    int read_layer_idx;
    int read_blob_idx;
  };

};  // namespace fertilized
#endif // CAFFE_FEATURE_EXTRACTION_ENABLED
#endif // FERTILIZED_FEATURE_EXTRACTION_DNNFEATURE_EXTRACTOR_H_
