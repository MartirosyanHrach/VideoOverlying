#ifndef TRACKER
#define TRACKER

#include "opencv2/opencv.hpp"
#include "opencv2/tracking.hpp"
#include <string>
#include <set>
#include <vector>
#include "Reader.hpp"
#include "MyException.hpp"

class Tracker {
public:
    Tracker(const Reader& reader, const std::string& trackingMethod);
    std::vector<cv::Mat>& getMasks() {return m_masks;}
    
private:
    void createTrackerByName(const std::string& trackerType);
    void getRandomColors(std::vector<cv::Scalar> &colors);
    void multiTracker(const std::vector<cv::Mat>& inputVideo);
    
private:
    cv::Ptr<cv::Tracker> m_tracker;
    std::vector<cv::Mat> m_masks;
};

#endif // TRACKER