#include <iostream>
#include "Reader.hpp"
#include "Writer.hpp"
#include "Tracker.hpp"
#include "BackgroundSubtractor.hpp"
#include "Overlayer.hpp"
#include "Utilities.hpp"
#include "MyException.hpp"

/* From c++ 11 you can use try out of main function, to keep the main function clean.*/ 
int main(int argc, char** argv) try{ 
    
    if(argc < 4) {
        throw MyException("Number of arguments must be at least 4");
    }
    const std::string output_video_directory(argv[1]);
    const std::string background_video_path(argv[2]);

    /* Creates Video object from background video */
    auto background_video = Reader::read(background_video_path);
    BackgroundSubtractor backgroundSubtractor(BackgroundSubtractor::Algorithms::mog2);
    /* Subtractes background from background video object */
    auto subtracted_background = backgroundSubtractor.subtruct_background(background_video);

    constexpr int moving_objects_video_index = 3;
    for(int i = moving_objects_video_index; i < argc; ++i) {
        const std::string movingObjectsVideo(argv[i]);
        /* Creates Video object from moving video */
        auto moving_objects_video = Reader::read(movingObjectsVideo);
        Tracker moving_object_tracker(Tracker::Algorithms::CSRT);
        /* Create mask for overlaying */
        auto moving_objects_masks = moving_object_tracker.track_objects(moving_objects_video);
        
        /* Get final overlayed video */
        auto result = Overlayer::overlay_videos(subtracted_background, moving_objects_video, moving_objects_masks);

        std::string output_video_path = Utilities::get_output_video_path(output_video_directory, argc - i);
        /* Writes to the file */
        Writer::write_to_file(output_video_path, result);
    }
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