#include "Reader.hpp"
#include <experimental/filesystem>

Reader::Reader(const std::string& fileName) {

    if(!std::experimental::filesystem::exists(fileName)) {
        throw MyException(fileName, " path is not found during import. Please be carefull :)");
    }

    cv::VideoCapture videoStream(fileName);

    if (!videoStream.isOpened()) {
        throw MyException(fileName, " file exists, but stream can not be open.");
    }
    
    m_width = 700;
    m_height = 700;
    m_frameCount = videoStream.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_COUNT);
    m_fps = videoStream.get(cv::VideoCaptureProperties::CAP_PROP_FPS);
    m_fourcc = videoStream.get(cv::VideoCaptureProperties::CAP_PROP_FOURCC);
    initializeVideo(videoStream);

    videoStream.release();
}

Reader::~Reader() { m_videoFrames.clear(); }

void Reader::initializeVideo(cv::VideoCapture& videoStream) {
    m_videoFrames.clear();
int i = 0;    
    cv::Mat frame, klir;
    while(true){

        /* Capture frame-by-frame */
        videoStream >> klir;
        if(klir.empty()) {
            break;
        }
        cv::resize(klir, frame, cv::Size(m_width, m_width));

        m_videoFrames.emplace_back(std::move(frame));
    }
}