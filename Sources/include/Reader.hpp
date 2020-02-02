#ifndef VIDEO_READER
#define VIDEO_READER

#include <string>
#include <opencv2/opencv.hpp>
#include "MyException.hpp"

/**
 * @brief   This class intends to read videos frame by frame
 *          and store as vector of Mat.
 */
class Reader {
public:
    /**
     * @brief   Constructor to read the video file.
     * 
     */
    explicit Reader(const std::string& file);

    /**
     * @brief   Destructor of the Reader class.   
    **/
   ~Reader();

    /*************
     *  GETTERS  *
     *************/
    int getWidth()                                  const { return m_width; }
    int getHeight()                                 const { return m_height; }
    int getFrameCount()                             const { return m_frameCount; }
    int getCodecNumber()                            const { return m_fourcc; }
    double getFrameRate()                           const { return m_fps; }
    const std::vector<cv::Mat>& getVideoFrames()    const { return m_videoFrames; } 

private:
    /**
     * @brief       Initializes vector of Mats reading frames from VideCaputure object.
     * @param[in]   videoStream -  VideoCapture object.
     */   
    void initializeVideo(cv::VideoCapture& videoStream);

private:
    int m_width;                        /* Width of input video. */    
    int m_height;                       /* Height of input video. */
    int m_frameCount;                   /* Frame count of input video. */
    int m_fourcc;                       /* Codec number of the input video */
    double m_fps;                       /* Frame rate of input video. */
    std::vector<cv::Mat> m_videoFrames; /* Container to hold the video frame by frame. */
};

#endif // VIDEO_READER