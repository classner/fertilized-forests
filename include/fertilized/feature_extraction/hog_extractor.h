/*
 * hog_extractor.h
 *
 *  Created on: Mar 22, 2012
 *      Author: mdantone
 * Minor edits by Christoph Lassner.
 */
#ifndef HOG_EXTRACTOR_H_
#define HOG_EXTRACTOR_H_

#include "../global.h"
#ifdef WITH_OPENCV
#include "hog/hog.h"

namespace fertilized {
namespace vision {
namespace features {
namespace feature_channels {

/** Utility class to encapsulate some precalculated values for the feature extraction. */
class HOGExtractor {
public:
  /** Extracts the feature channels as used in the original Hough forest publications by Juergen Gall (32 layers). */
  void extractFeatureChannels32(const cv::Mat& img,
                                std::vector<cv::Mat>& channels);

  /** Extracts the feature channels as used in the publications by Matthias Dantone (15 layers). */
  void extractFeatureChannels15(const cv::Mat& img,
                                std::vector<cv::Mat>& channels);

  /** Max filter utility function. */
  static void maxfilt(cv::Mat &src, unsigned int width);

  /** Min filter utility function. */
  static void minfilt(cv::Mat &src, cv::Mat &dst, unsigned int width);

  /** Max filter utility function. */
  static void maxfilt(uchar* data, uchar* maxvalues, unsigned int step,
                      unsigned int size, unsigned int width);

  /** Max filter utility function. */
  static void maxfilt(uchar* data, unsigned int step, unsigned int size,
                      unsigned int width);

  /** Min filter utility function. */
  static void minfilt(uchar* data, uchar* minvalues, unsigned int step,
                      unsigned int size, unsigned int width);

  /** Min filter utility function. */
  static void minfilt(uchar* data, unsigned int step, unsigned int size,
                      unsigned int width);

private:
  HoG hog;
};

} // namespace vision
} // namespace features
} // namespace feature_channels
} // namespace fertilized
#endif // WITH_OPENCV
#endif /* HOG_EXTRACTOR_H_ */
