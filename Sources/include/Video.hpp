#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <opencv2/opencv.hpp>

/**
 *  @brief  This struct binds all the needed properties that OpenCV need
 *          to process with video objects. 
 *          Implemented as struct, because it doesn't have functionalty,
 *          it just binds data related to video. 
 **/
struct Video {
public:
    /**
     *  @brief Creates Video object with specified parameters.
     *  @param[in]  width   - The width of the video
     *  @param[in]  img     - The height of the video
     *  @param[in]  img     - The frame count of the video
     *  @param[in]  cont    - The codec number of the video converted by OpenCV nubmers
     *  @param[in]  cont    - The frame rate of the video
     **/    
    Video(int width, int height, int frame_count, int fourcc, double frame_rate)
        : m_width(width)
        , m_height(height)
        , m_frame_count(frame_count)
        , m_fourcc(fourcc)
        , m_frame_rate(frame_rate)
        , m_frames(frame_count) {}

public:
    int m_width;                    /* The widths of video frames */
    int m_height;                   /* The height of video frames */
    int m_frame_count;              /* Number of frames of the video */
    int m_fourcc;                   /* Appropriate codec number converted by OpenCV */
    double m_frame_rate;            /* Frame rate of video */
    std::vector<cv::Mat> m_frames;  /* Container to hold video:frame by frame */
};

#endif // VIDEO_HPP