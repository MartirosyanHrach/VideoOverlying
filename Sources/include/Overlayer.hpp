#ifndef OVERLAYER
#define OVERLAYER

#include <string>
#include "Reader.hpp"
#include "Writer.hpp"
#include "Tracker.hpp"
#include "BackgroundSubtractor.hpp"
#include "MyException.hpp"

class Overlayer {
public:
    Overlayer(const std::string& backgroundVideoName, const std::string& movingObjectsVideoName, const std::string& outputFileName, 
        const std::string& trackingAlgorithm = "MEDIANFLOW", const std::string& backgroundSubtractionAlgorithm = "mog2");
    
    /*************
     *  SETTERS  *
     *************/    
    void setOutputVideCodecNumber(int codecNumber);
    void setOutputWidth(int width);
    void setOutputHeight(int height);
    void setOutputFrameRate(double frameRate);
    void setTrackingAlgorithm(const std::string& trackingAlgorithm);
    void setBackgroundSubtractionAlgorithm(const std::string& backgroundSubtractionAlgorithm);

    void writeToFile();
private:
    void overlayFrameByFrame(const Reader& movingVideo, const BackgroundSubtractor& subtractedBackground);

private:
    int m_codecNumber;
    int m_width;
    int m_height;
    double m_frameRate;
    std::string m_trackingAlgorithm;
    std::string m_backgroundSubtractionAlgorithm;
    std::string m_outputFileName;
    std::vector<cv::Mat> m_outputVideFrames;
};

#endif //OVERLAYER