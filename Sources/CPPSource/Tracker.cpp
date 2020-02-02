#include "Tracker.hpp"


Tracker::Tracker(const Reader& reader, const std::string& trackingMethod) {
    createTrackerByName(trackingMethod);
    multiTracker(reader.getVideoFrames());
}

Tracker::~Tracker() { m_masks.clear(); }

void Tracker::createTrackerByName(const std::string& trackerType) {
    if(trackerType == "BOOSTING"){
        m_tracker = cv::TrackerBoosting::create();
    }
    else if(trackerType == "MIL"){
        m_tracker = cv::TrackerMIL::create();
    }
    else if(trackerType == "KCF"){
        m_tracker = cv::TrackerKCF::create();
    }
    else if(trackerType == "TLD"){
        m_tracker = cv::TrackerTLD::create();
    }
    else if(trackerType == "MEDIANFLOW"){
        m_tracker = cv::TrackerMedianFlow::create();
    }
    else if(trackerType == "GOTURN"){
        m_tracker = cv::TrackerGOTURN::create();
    }
    else if(trackerType == "MOSSE"){
        m_tracker = cv::TrackerMOSSE::create();
    }
    else if(trackerType == "CSRT"){
        m_tracker = cv::TrackerCSRT::create();
    }
    else {
        throw MyException(trackerType, "is unsupported tracking algorithm.");
    }
}


void Tracker::getRandomColors(std::vector<cv::Scalar> &colors) {
    cv::RNG rng(0);
    for (size_t i = 0; i < colors.size(); ++i) {
        colors[i] = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    }
}

void Tracker::multiTracker(const std::vector<cv::Mat>& inputVideo) {
	if(inputVideo.empty()) {
        throw MyException("Input vide is empty.");
    }

    std::vector<cv::Rect> bboxes;
    cv::Mat frame = inputVideo[0];
	cv::selectROIs("MultiTracker", frame, bboxes, true, false);

	/* Quit if there are no objects to track */
	if(bboxes.size() < 1) {
        throw MyException("No objects detected to track");
    }

    std::vector<cv::Scalar> colors(bboxes.size());
	getRandomColors(colors);

    cv::Ptr<cv::MultiTracker> multiTracker = cv::MultiTracker::create();
	for(size_t i = 0; i < bboxes.size(); ++i) {
		multiTracker->add(m_tracker, frame, cv::Rect2d(bboxes[i]));    
    }
    
    for(size_t i = 0; i < inputVideo.size(); ++i) {
        frame = inputVideo[i];
        multiTracker->update(frame);
        cv::Mat mask = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
        for (size_t i = 0; i < multiTracker->getObjects().size(); ++i) {
            cv::rectangle(frame, multiTracker->getObjects()[i], colors[i], 2, 1);
            cv::grabCut(frame, mask, multiTracker->getObjects()[i], cv::Mat(), cv::Mat(), 5, cv::GC_INIT_WITH_RECT);

            cv::compare(mask, cv::GC_PR_FGD, mask,cv::CMP_EQ);
            m_masks.emplace_back(mask);
        }
    }

}