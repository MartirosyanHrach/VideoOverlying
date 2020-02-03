#ifndef UTILITIES
#define UTILITIES
#include <string>
#include <experimental/filesystem>
#include "MyException.hpp" 

/** 
 *  @brief  The namespace is for utility functions.
 *          This can be updated in future.
 */
namespace Utilities {
    using Path = std::experimental::filesystem::path;
    using CmdArgs = std::tuple<Path,
                           Path,
                           std::vector<Path>>;
    /**
     *  @brief      Generates output file path, from output video directory and moving object index.
     *  @param[in]  output_video_directory  - file directory where to write output videos.
     *  @param[out] Video                   - output file path.
     **/
    Path get_output_video_path(const Path& output_video_directory, int index);

    /**
     *  @brief  Resolves command line arguments.
     **/
    CmdArgs resolve_command_line_arguments(int argc, char** argv);
}


#endif //UTILITIES