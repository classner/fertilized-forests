/* Author: Christoph Lassner. */
#ifndef FERTILIZED_FEATURE_EXTRACTION_H_
#define FERTILIZED_FEATURE_EXTRACTION_H_

#include "../global.h"
#include "../ndarray.h"

#include <cstdint>

namespace fertilized {
    /**
     * Extract the Hough forest features. If `full` is set, uses the 
     * 32 feature channels used by Juergen Gall in his original publications,
     * else use 15 feature channels as used by Matthias Dantone.
     *
     * The image must be in OpenCV (BGR) channel format!
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
     * \param image Array<uint8_t>, row-major contiguous
     *   The source image.
     * \param full bool
     *   Whether to return the full feature set (32 layers) or not (15 layers).
     *   Default: false.
     */
    DllExport Array<uint8_t, 3, 3> extract_hough_forest_features(
                                    const Array<uint8_t const, 3, 3> &image,
                                    const bool &full=false);

}  // namespace fertilized
#endif // FERTILIZED_FEATURE_EXTRACTION_H_
