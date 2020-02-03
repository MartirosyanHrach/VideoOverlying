#ifndef OVERLAYER
#define OVERLAYER

#include <string>
#include "Reader.hpp"
#include "Writer.hpp"
#include "Tracker.hpp"
#include "BackgroundSubtractor.hpp"
#include "MyException.hpp"

/**
 * @brief   This class implements only one static function,
 *          which performs overlaying process.
 *          Expects 3 arguments:
 *              1. Background subtractted video(with already removed moving objects from background).
 *              2. Video of moving objects. 
 *              3. Mask of moving object, which created by class Tracker.
 */
class Overlayer {
public:
    /**
     *  @brief      Selects only largest components in the binary image
     *  @param[in]  subtracted_background   - subtracted background video 
     *  @param[in]  moving_objects_video    - moving objects video
     *  @param[in]  moving_objects_mask     - moving objects mask video
     *  @param[out] Video                   - Destination video already overlayed
     **/
    static Video overlay_videos(const Video& subtracted_background, const Video& moving_objects_video, const Video& moving_objects_mask);
};

#endif //OVERLAYER