#include <iostream>
#include "Reader.hpp"
#include "Writer.hpp"
#include "Tracker.hpp"
#include "BackgroundSubtractor.hpp"
#include "Overlayer.hpp"
#include "Utilities.hpp"
#include "MyException.hpp"
#include "Timer.hpp"

/* From c++ 11 you can use try out of main function, to keep the main function clean.*/ 
int main(int argc, char** argv) try{ 
    /* Timer class object to calculate te excecution time.*/
    Timer timer;
    const auto cmd_args = Utilities::resolve_command_line_arguments(argc, argv);
    const auto output_video_directory(std::get<0>(cmd_args));
    const auto background_video_path(std::get<1>(cmd_args));
    const auto moving_objects_video_paths(std::get<2>(cmd_args));

    /* Creates Video object from background video */
    const auto background_video = Reader::read(background_video_path);
    BackgroundSubtractor backgroundSubtractor(BackgroundSubtractor::Algorithms::mog2);
    /* Subtractes background from background video object */
    const auto subtracted_background = backgroundSubtractor.subtruct_background(background_video);

    int unique_id = 1;
    for (const auto moving_objects_video_path : moving_objects_video_paths) {
        /* Creates Video object from moving video */
        const auto moving_objects_video = Reader::read(moving_objects_video_path);
        Tracker moving_object_tracker(Tracker::Algorithms::CSRT);
        /* Create mask for overlaying */
        const auto moving_objects_masks = moving_object_tracker.track_objects(moving_objects_video);
        
        /* Get final overlayed video */
        const auto result = Overlayer::overlay_videos(subtracted_background, moving_objects_video, moving_objects_masks);

        const auto output_video_path = Utilities::get_output_video_path(output_video_directory, unique_id++);
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