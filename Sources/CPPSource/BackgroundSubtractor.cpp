#include "BackgroundSubtractor.hpp"

BackgroundSubtractor::BackgroundSubtractor(Algorithms algorithm_type) {
        if (algorithm_type == Algorithms::knn) {
            m_subtraction_model = cv::createBackgroundSubtractorKNN();
        }
        else if (algorithm_type == Algorithms::mog2) {
            m_subtraction_model = cv::createBackgroundSubtractorMOG2();
        }
        else {
            throw MyException("Unsupported background subtraction method.");
        }
}

Video BackgroundSubtractor::subtruct_background(const Video& input_video) {
    if(input_video.m_frames.empty()) {
        throw MyException("Input video is empty.");
    }
        
    Video background_video(
        input_video.m_width,
        input_video.m_height,
        input_video.m_frame_count,
        input_video.m_fourcc,
        input_video.m_frame_rate
    );

    cv::Mat background;
    for(int i = 0; i < background_video.m_frame_count; ++i) {
        m_subtraction_model->apply(input_video.m_frames[i], background);
        m_subtraction_model->getBackgroundImage(background);
        background_video.m_frames[i] = std::move(background);
    }
    return background_video;
}