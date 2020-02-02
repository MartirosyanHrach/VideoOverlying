#include "BackgroundSubtractor.hpp"

BackgroundSubtractor::BackgroundSubtractor(const Reader& reader, const std::string& method) : 
    m_subtractionMethod(method) {
        if (m_subtractionMethod == "knn") {
            m_subtractionModel = cv::createBackgroundSubtractorKNN();
        }
        else if (m_subtractionMethod == "mog2") {
            m_subtractionModel = cv::createBackgroundSubtractorMOG2();
        }
        else {
            throw MyException(m_subtractionMethod, "is unsupported subtraction method.");
        }

        /* Here we pass already frame by frame stored Mat object to the main background subtractor function.*/
        getBackgroundFromInputVideo(reader.getVideoFrames());
}

void BackgroundSubtractor::getBackgroundFromInputVideo(const std::vector<cv::Mat>& video) {
    cv::Mat background;
    for(size_t i = 0; i < video.size(); ++i) {
        m_subtractionModel->apply(video[i], background);
        m_subtractionModel->getBackgroundImage(background);
        m_backgroundContainer.emplace_back(std::move(background));
    }
}