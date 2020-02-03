#ifndef UTILITIES
#define UTILITIES
#include <string>

/** 
 *  @brief  The namespace is for utility functions.
 *          This can be updated in future.
 */
namespace Utilities {
    /**
     *  @brief      Generates output file path, from output video directory and moving object index.
     *  @param[in]  output_video_directory  - file directory where to write output videos.
     *  @param[out] Video                   - output file path.
     **/  
    std::string get_output_video_path(const std::string& output_video_directory, int index) {
        return output_video_directory + "Output_Video" + std::to_string(index) + ".mp4";
    }
}


#endif