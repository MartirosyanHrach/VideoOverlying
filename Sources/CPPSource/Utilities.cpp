#include "Utilities.hpp"

Utilities::Path Utilities::get_output_video_path(const Path& output_video_directory, int index) {
    const std::string filename = "Output_Video" + std::to_string(index) + ".mp4";
    return output_video_directory / filename;
}

/**
 *  @brief  Resolves command line arguments.
 **/
Utilities::CmdArgs Utilities::resolve_command_line_arguments(int argc, char** argv) {
    if(argc < 4) {
        throw MyException("Number of arguments must be at least 4");
    }

    constexpr int CMD_ARG_OUTPUT_VIDEO_DIRECTORY = 1;
    constexpr int CMD_ARG_BACKGROUND_VIDEO_PATH = 2;
    constexpr int CMD_ARG_FIRST_MOVING_VIDEO_PATH = 3;

    std::vector<Utilities::Path> moving_video_paths;
    std::copy(&argv[CMD_ARG_FIRST_MOVING_VIDEO_PATH], &argv[argc], std::back_inserter(moving_video_paths));
    return {
        Utilities::Path(argv[CMD_ARG_OUTPUT_VIDEO_DIRECTORY]),
        Utilities::Path(argv[CMD_ARG_BACKGROUND_VIDEO_PATH]),
        moving_video_paths
    };
}