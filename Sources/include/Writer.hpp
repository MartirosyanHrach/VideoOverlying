#ifndef VIDEO_WRITER
#define VIDEO_WRITER

#include <string>
#include <opencv2/opencv.hpp>
#include "MyException.hpp"

/**
 * @brief   This class intends to create video file
 *          and write the specified data to that file.
 */
class Writer {
public:
    /**
     * @brief       Constructs cv::VideoWriter object.
     * @param[in]   outputFileName  - Output file name.
     * @param[in]   fourcc  - The codec number of the output video.
     * @param[in]   fps  - The frame rate of the output video.
     * @param[in]   width  - Output width of the output video.
     * @param[in]   height  - Output height of the output video.
     */  
    explicit Writer(const std::string& outputFileName, int fourcc, double fps, int width, int height);

    /**
     * @brief       The overlodaded version of constructor. Specifies codec
     *              as string. 
     * @param[in]   outputFileName  - Output file name.
     * @param[in]   codec  - The codec name of the output video.
     * @param[in]   fps  - The frame rate of the output video.
     * @param[in]   width  - Output width of the output video.
     * @param[in]   height  - Output height of the output video.
     */    
    explicit Writer(const std::string& outputFileName, const std::string& codec, double fps, int width, int height);

    /**
     * @brief       Get file extension, to check whether specified extension is supported.
     * @param[in]   outputFileName  - Output file name.
     */  
    void writeToFile(const std::vector<cv::Mat>& videoFrames);
    
private:
    /**
     * @brief       Get file extension, to check whether specified extension is supported.
     * @param[in]   outputFileName  - Output file name.
     */  
    std::string getFileExtension(const std::string& outputFileName);

    /**
     * @brief       Validate and return OpenCV's appropriate codec number.
     * @param[in]   outputFileName  - To get extension of the video file.
     * @param[in]   codec           - The codec name.
     */   
    int getFourcc(const std::string& outputFileName, const std::string& codec);

private:
    int m_fourcc;                   /* Codec number of output video. */
    double m_fps;                   /* Frame rate of output video. */
    cv::Size m_size;                /* cv::Size object, which hold width and height of output video. */
    std::string m_outputFileName;   /* Output file name. */
};

#endif // VIDEO_WRITER