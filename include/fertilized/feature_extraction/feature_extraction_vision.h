/* Author: Christoph Lassner. */

#ifndef FERTILIZED_FEATURE_EXTRACTION_VISION_H_
#define FERTILIZED_FEATURE_EXTRACTION_VISION_H_

#include <vector>

#include "../global.h"
#ifdef WITH_OPENCV
#include <opencv2/opencv.hpp>
#include "./hog_extractor.h"

namespace fertilized {
    /**
     * Extract the Hough forest features. If `full` is set, uses the
     * 32 feature channels used by Juergen Gall in his original publications,
     * else use 15 feature channels as used by Matthias Dantone.
     *
     * The image must be in OpenCV (BGR) channel format!
     *
     * \param image Array<uint8_t>, row-major contiguous
     *   The source image.
     * \param full bool
     *   Whether to return the full feature set (32 layers) or not (15 layers).
     *   Default: false.
     */
    DllExport std::vector<cv::Mat> extract_hough_forest_features(
                                                  const cv::Mat &image,
                                                  const bool &full=false);
}  // namespace fertilized
#endif // WITH_OPENCV
#endif // FERTILIZED_FEATURE_EXTRACTION_VISION_H_
