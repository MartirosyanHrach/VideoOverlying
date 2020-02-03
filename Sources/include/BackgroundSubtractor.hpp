#ifndef BACKGROUND_SUBTSRACTOR
#define BACKGROUND_SUBTSRACTOR
#include <vector>
#include <opencv2/opencv.hpp>
#include "Reader.hpp"
#include "MyException.hpp"


/**
 * @brief   This class intends to subtract background of the video
 *          and store in the Video container to overlay with moving objects.
 */
class BackgroundSubtractor {
public:
    /* Supported background subtraction algorithms */
    enum Algorithms {mog2, knn};

    /**
     * @brief       Construct to subtracted background video.
     * @param[in]   subtraction_algorithm  - The subtraction algorithm name. It can be either knn or mog2.
     */ 
    BackgroundSubtractor(Algorithms algorithm_type);

    /**
     * @brief       Construct to subtracted background video and return it.
     * @param[in]   input_video - The Video object.
     * @param[out]  Video       - The subtracted Video object.
     */     
    Video subtruct_background(const Video& input_video); 
private:
    cv::Ptr<cv::BackgroundSubtractor> m_subtraction_model;  /* BackgroundSubtractor algorithm class pointer. */
};

#endif // BACKGROUND_SUBTSRACTOR