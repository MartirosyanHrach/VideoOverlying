#include "Tracker.hpp"

Video Tracker::track_objects(const Video& input_video) {
    if(input_video.m_frames.empty()) {
        throw MyException("Input video is empty.");
    }
    
    std::vector<cv::Rect> bboxes;
    cv::Mat frame = input_video.m_frames[0];
    /* Opens window, which waits user to select region of interests, in this case moving objects. */
	cv::selectROIs("MultiTracker", frame, bboxes, true, false);

	/* Quit if there are no objects to track */
	if(bboxes.size() < 1) {
        throw MyException("No objects detected to track");
    }

    std::vector<cv::Scalar> colors(bboxes.size());
	getRandomColors(colors);

    /* Creates multitracker object */
    cv::Ptr<cv::MultiTracker> multiTracker = cv::MultiTracker::create();
    /* Addes new object to be tracked */
	for(size_t i = 0; i < bboxes.size(); ++i) {
		multiTracker->add(m_tracker, frame, cv::Rect2d(bboxes[i]));    
    }

    /* Video object that has to be returned */
    Video masks(
        input_video.m_width,
        input_video.m_height,
        input_video.m_frame_count,
        input_video.m_fourcc,
        input_video.m_frame_rate
    );

    for(size_t i = 0; i < input_video.m_frames.size(); ++i) {
        frame = input_video.m_frames[i];
        /* Update the current tracking status */
        multiTracker->update(frame);
        /* Initializes mask with zeros with CV8_U type */
        cv::Mat mask = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
        for (unsigned int i = 0; i < multiTracker->getObjects().size(); ++i) {
            /* draws a rectangle outline */
            cv::rectangle(frame, multiTracker->getObjects()[i], colors[i], 2, 1);
            /* grabCut algorithm is used to perform background removal inside the tracked refion of interests. */
            cv::grabCut(frame, mask, multiTracker->getObjects()[i], cv::Mat(), cv::Mat(), 1, cv::GC_INIT_WITH_RECT);

            /* Compares and sets cv::CMP_EQ to mask */
            cv::compare(mask, cv::GC_PR_FGD, mask, cv::CMP_EQ);
        }
        masks.m_frames[i] = std::move(mask);
    }
    return masks;
}


Tracker::Tracker(Algorithms algorithm_type) {
    createTrackerByName(algorithm_type);
}

void Tracker::createTrackerByName(Algorithms algorithm_type) {
    if(algorithm_type == Algorithms::BOOSTING){
        m_tracker = cv::TrackerBoosting::create();
    }
    else if(algorithm_type == Algorithms::MIL){
        m_tracker = cv::TrackerMIL::create();
    }
    else if(algorithm_type == Algorithms::KCF){
        m_tracker = cv::TrackerKCF::create();
    }
    else if(algorithm_type == Algorithms::TLD){
        m_tracker = cv::TrackerTLD::create();
    }
    else if(algorithm_type == Algorithms::MEDIAN_FLOW){
        m_tracker = cv::TrackerMedianFlow::create();
    }
    else if(algorithm_type == Algorithms::GOTURN){
        m_tracker = cv::TrackerGOTURN::create();
    }
    else if(algorithm_type == Algorithms::MOSSE){
        m_tracker = cv::TrackerMOSSE::create();
    }
    else if(algorithm_type == Algorithms::CSRT){
        m_tracker = cv::TrackerCSRT::create();
    }
    else {
        throw MyException("Unsupported tracking algorithm.");
    }
}


void Tracker::getRandomColors(std::vector<cv::Scalar>& colors) {
    cv::RNG rng(0);
    for (size_t i = 0; i < colors.size(); ++i) {
        colors[i] = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    }
}