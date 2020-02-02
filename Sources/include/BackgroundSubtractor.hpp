#ifndef BACKGROUND_SUBTSRACTOR
#define BACKGROUND_SUBTSRACTOR
#include <vector>
#include <opencv2/opencv.hpp>
#include "Reader.hpp"
#include "MyException.hpp"


/**
 * @brief   This class intends to subtract background  of the video
 *          and store in the container to overlay with moving objects.
 */
class BackgroundSubtractor {
public:
    /**
     * @brief       Construct to subtract the background of the video.
     * @param[in]   reader  - The reader object, from which the background must be subtracted.
     * @param[in]   method  - The subtraction algorithm name. It can be either knn or mog2.
     */ 
    BackgroundSubtractor(const Reader& reader, const std::string& method);

    /*************
     *  GETTERS  *
     *************/
    const std::vector<cv::Mat>& getBackground() const { return m_backgroundContainer; }
    
private:
    /**
     * @brief       This function recives vetor of frames(Mat objects), extracts backgrounds and stores in m_backgroundContainer.
     * @param[in]   video   - The input video, from which background must be extracted.
     */ 
    void getBackgroundFromInputVideo(const std::vector<cv::Mat>& video);

private:
    std::string m_subtractionMethod;                        /* The subtraction method. */
    std::vector<cv::Mat> m_backgroundContainer;             /* The container to hold the extracted video. */
    cv::Ptr<cv::BackgroundSubtractor> m_subtractionModel;   /* BackgroundSubtractor class pointer. */
};

#endif // BACKGROUND_SUBTSRACTOR