#ifndef VIDEO_READER
#define VIDEO_READER

#include <experimental/filesystem>
#include "Video.hpp"
#include <opencv2/opencv.hpp>
#include "MyException.hpp"

/**
 * @brief   This class intends to read video stream.
 *          As this class is more action, it reads the video
 *          from file, it only has static read function, which returns
 *          Video object, initialized with input video. 
 */
class Reader {
public:
    /**
     *  @brief      Reads the image from input_file_name
     *  @param[in]  input_file_name - file name from which video must be read
     *  @param[out] Video           - video object, initialized with input_file_name video file.
     **/    
    static Video read(const std::experimental::filesystem::path& input_file_name);

private:
    /**
     *  @brief      Validates input file. If file doesn't exist or Video stream can't be opened throws appropriate exception. 
     *  @param[in]  input_file_name      - file name which must be validated
     *  @param[out] cv::VideoCapture    - if exception is not thrown, return cv::VideoCapture object
     **/    
    static cv::VideoCapture validate_input_file(const std::experimental::filesystem::path& input_file_name);
};

#endif // VIDEO_READER