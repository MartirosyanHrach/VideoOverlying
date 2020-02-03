#include "Reader.hpp"
#include <experimental/filesystem>

cv::VideoCapture Reader::validate_input_file(const std::string& input_file_name) {
    /* Check if file exists */
    if(!std::experimental::filesystem::exists(input_file_name)) {
        throw MyException(input_file_name, " path is not found during import. Please be carefull :)");
    }

    cv::VideoCapture videoStream(input_file_name);
    /* Check if video stream opened successfully */
    if (!videoStream.isOpened()) {
        throw MyException(input_file_name, " file exists, but stream can not be open.");
    }
    return videoStream;
}

Video Reader::read(const std::string& input_file_name) {
    auto video_stream = validate_input_file(input_file_name);
    
    /* 
        As input video streams can have big sizes,
        we resize original video frames to {700, 700}.
        Note: This is temporary solution.   
    */
    constexpr int width = 700;
    constexpr int height = 700; 
    Video input_video(
        width,
        height,
        video_stream.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_COUNT),
        video_stream.get(cv::VideoCaptureProperties::CAP_PROP_FOURCC),
        video_stream.get(cv::VideoCaptureProperties::CAP_PROP_FPS)
    );

    cv::Mat frame;
    for (int i = 0; i < input_video.m_frame_count; ++i) {
        /* Read frame by frame and write temporary frame object */
        video_stream >> frame;
        cv::resize(frame, frame, cv::Size(input_video.m_width, input_video.m_height));
        input_video.m_frames[i] = std::move(frame);
    }
    return input_video;
}