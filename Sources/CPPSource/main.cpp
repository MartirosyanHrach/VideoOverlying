#include <iostream>
#include "Reader.hpp"
#include "Writer.hpp"
#include "Tracker.hpp"
#include "BackgroundSubtractor.hpp"
#include "Overlayer.hpp"
#include "MyException.hpp"

/* From c++ 11 you can use try out of main function, to keep the main function clean.*/ 
int main() try{ 
    
        const std::string backgroundVideo = "/home/hrach/Downloads/background.mp4";
        const std::string movingObjectsVideo = "/home/hrach/Downloads/book.mp4";
        const std::string outputVideo = "/home/hrach/Downloads/OutputVideo.mp4";

        auto background_video = Reader::read(backgroundVideo);
        BackgroundSubtractor backgroundSubtractor(BackgroundSubtractor::Algorithms::mog2);
        auto subtracted_background = backgroundSubtractor.subtruct_background(background_video);
        
        auto moving_objects_video = Reader::read(movingObjectsVideo);
        Tracker moving_object_tracker(Tracker::Algorithms::CSRT);
        auto moving_objects_masks = moving_object_tracker.track_objects(moving_objects_video);
        
        auto result = Overlayer::overlay_videos(subtracted_background, moving_objects_video, moving_objects_masks);
        
        Writer::write_to_file(outputVideo, result);
}
catch(MyException& e) {
    std::cerr << e.what() << std::endl;
}
catch(std::exception& e) {
    std::cout << e.what() << std::endl;
}
catch(...) {
    std::cout << "Unknown exception cought" << std::endl;
}