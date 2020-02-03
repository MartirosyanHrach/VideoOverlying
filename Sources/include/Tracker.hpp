#ifndef TRACKER
#define TRACKER

#include "opencv2/opencv.hpp"
#include "opencv2/tracking.hpp"
#include <string>
#include <vector>
#include <set>
#include "Reader.hpp"
#include "MyException.hpp"

/**
 * @brief   This class intends to perform objact tracking
 *          via cv::Tracker algorithm. You can specify any of 
 *          {BOOSTING, MIL, KCF, TLD, MEDIAN_FLOW, GOTURN, MOSSE, CSRT} algorithms.
 *          Certain algorithms allow us to use multitracking.
 *          Once moving_object_tracker function is called, it opens
 *          a windows where user can select ROI(Region of interests) of objects,
 *          which then will be tracked.
 */
class Tracker {
public:
    /* Supported tracking algorithms */
    enum Algorithms {BOOSTING, MIL, KCF, TLD, MEDIAN_FLOW, GOTURN, MOSSE, CSRT};
    
    /**
     *  @brief      Reads the image from input_file_name
     *  @param[in]  algorithm_type - the algorithm type
     **/    
    Tracker(Algorithms algorithm_type);

    /**
     *  @brief      Reads the image from input_file_name
     *  @param[in]  algorithm_type  - the input video, from which object must be detected
     *  @param[out] Video           - tracked moving object mask's video
     **/    
    Video track_objects(const Video& input_video);
    
private:
    /**
     *  @brief      Initializes appropriate tracking algorithm depends on input argument 
     *  @param[in]  algorithm_type - the algorithm type, from which cv::Tracker will be initialized
     **/
    void createTrackerByName(Algorithms algorithm_type);
    
    /**
     *  @brief      Initializes vector with cv::Scalar objects
     *  @param[in]  colors - the input vector
     **/
    void getRandomColors(std::vector<cv::Scalar>& colors);
    
private:
    cv::Ptr<cv::Tracker> m_tracker; /* Pointer, which will point to appropriate Tracker algorithm object. */
};

#endif // TRACKER