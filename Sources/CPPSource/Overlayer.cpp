#include "Overlayer.hpp" 


Overlayer::Overlayer(const std::string& backgroundVideoName, const std::string& movingObjectsVideoName, const std::string& outputFileName,
    const std::string& trackingAlgorithm, const std::string& backgroundSubtractionAlgorithm) :
        m_outputFileName(outputFileName), 
        m_trackingAlgorithm(trackingAlgorithm),
        m_backgroundSubtractionAlgorithm(backgroundSubtractionAlgorithm) {

        Reader backgroundVideo(backgroundVideoName);
        Reader movingVideo(movingObjectsVideoName);
        
        /* 
            User can explicitly set output video parameters.
            If not set Writer class will use background's video parameters.
        */            
        m_codecNumber =  backgroundVideo.getCodecNumber();
        m_width = backgroundVideo.getWidth();
        m_height = backgroundVideo.getHeight();
        m_frameRate = backgroundVideo.getFrameRate();
        /* 
            Also users can explicitly set tracking and background
            subtraction algorithms.
        */              
        m_trackingAlgorithm = "MEDIANFLOW";
        m_backgroundSubtractionAlgorithm = "mog2";
        BackgroundSubtractor background(backgroundVideo, m_backgroundSubtractionAlgorithm);

        overlayFrameByFrame(movingVideo, background);
}

void Overlayer::overlayFrameByFrame(const Reader& movingVideo, const BackgroundSubtractor& subtractedBackground) {

    auto& movingVideoFrames = movingVideo.getVideoFrames();
    auto& backgroundVideoFrames = subtractedBackground.getBackground();

    Tracker trackedObjects(movingVideo, m_trackingAlgorithm);
    auto& trackedObjectFrames = trackedObjects.getMasks();
    
    auto minFrameSize = (movingVideoFrames.size() < backgroundVideoFrames.size()) ? movingVideoFrames.size() : backgroundVideoFrames.size();

    cv::Mat tmpMoving, tmpBackground, inverseMask;
    m_outputVideFrames.resize(minFrameSize);

    for(size_t i = 0; i < minFrameSize; ++i) {
        cv::bitwise_not(movingVideoFrames[i], inverseMask);
        tmpMoving = trackedObjectFrames[i];
        tmpMoving.setTo(0, inverseMask);
        tmpBackground = backgroundVideoFrames[i];
        tmpBackground.setTo(0, trackedObjectFrames[i]);
        m_outputVideFrames[i] = tmpMoving + tmpBackground;
    }
}

void Overlayer::writeToFile() {
    Writer write(m_outputFileName, m_codecNumber, m_frameRate, m_width, m_height);
    write.writeToFile(m_outputVideFrames);
}

void Overlayer::setOutputVideCodecNumber(int codecNumber) {
    m_codecNumber = codecNumber;
}
void Overlayer::setOutputWidth(int width) {
    m_width = width;
}
void Overlayer::setOutputHeight(int height) {
    m_height = height;
}
void Overlayer::setOutputFrameRate(double frameRate) {
    m_frameRate = frameRate;
}
void Overlayer::setTrackingAlgorithm(const std::string& trackingAlgorithm) {
    m_trackingAlgorithm = trackingAlgorithm;
}
void Overlayer::setBackgroundSubtractionAlgorithm(const std::string& backgroundSubtractionAlgorithm) {
    m_backgroundSubtractionAlgorithm = backgroundSubtractionAlgorithm;
}