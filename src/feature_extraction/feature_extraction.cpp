/* Author: Christoph Lassner. */
#include "fertilized/feature_extraction/feature_extraction.h"
#include "fertilized/feature_extraction/feature_extraction_vision.h"

#ifdef WITH_OPENCV
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif

#include <vector>
#include <algorithm>

#include "fertilized/ndarray.h"

#include "fertilized/global.h"
#include "fertilized/types.h"
#include "fertilized/util/gil.hpp"
#include "fertilized/feature_extraction/hog_extractor.h"

#ifdef WITH_OPENCV
namespace ft = fertilized::vision::features::feature_channels;
#endif
#ifdef PYTHON_ENABLED
namespace py = boost::python;
#endif

namespace fertilized {
#ifdef WITH_OPENCV
    ft::HOGExtractor HOG_EXTRACTOR = ft::HOGExtractor();

    DllExport std::vector<cv::Mat> extract_hough_forest_features(
                                                const cv::Mat &image,
                                                const bool &full) {
      std::vector<cv::Mat> res(0);
      if (full) {
        HOG_EXTRACTOR.extractFeatureChannels32(image, res);
      } else {
        HOG_EXTRACTOR.extractFeatureChannels15(image, res);
      }
      return res;
    };
#endif

    DllExport Array<uint8_t, 3, 3> extract_hough_forest_features(
                                                const Array<uint8_t const, 3, 3> &image,
                                                const bool &full) {
      if (image.TPLMETH getSize<2>() != 3) {
        throw Fertilized_Exception("The image must be a 3-channel color image!");
      }
      size_t n_channels = 15;
      if (full) {
        n_channels = 32;
      }
      // Construct the result array.
      Array<uint8_t, 3, 3> result = allocate(makeVector(n_channels,
                                                        image.getSize<0>(),
                                                        image.getSize<1>()));
#ifdef WITH_OPENCV
      // Checks done. The rest can happen in parallel.
      {
#ifdef PYTHON_ENABLED
        py::gil_guard_release gil_guard;
#endif
        // Construct an OpenCV mat.
        const cv::Mat im_cvm = cv::Mat(static_cast<int>(image.getSize<0>()),
                                       static_cast<int>(image.getSize<1>()),
                                       CV_8UC3,
                                       reinterpret_cast<void*>(const_cast<uint8_t*>(image.getData())));
        std::vector<cv::Mat> resvec = extract_hough_forest_features(im_cvm,
                                                                    full);
        // Copy the results to the array.
        uint8_t *resptr = reinterpret_cast<uint8_t*>(result.getData());
        for (int i = 0; i < n_channels; ++i) {
          // Copy row-wise, since this is the only guaranteed way to work with
          // OpenCV.
          for (int row = 0; row < resvec[i].rows; ++row) {
            std::copy(resvec[i].ptr<uint8_t>(row),
                      resvec[i].ptr<uint8_t>(row) + resvec[i].cols,
                      resptr +
                        i * image.getSize<0>() * image.getSize<1>() +
                        row * resvec[i].cols);
          }
        }
      }
#else
    throw Fertilized_Exception("The library has been built without OpenCV and "
                               "feature extraction is not available!");
#endif
      return result;
    };
}  // namespace fertilized
