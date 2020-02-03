#include "Writer.hpp"
#include <set>
#include <opencv2/opencv.hpp>
#include "MyException.hpp"

void Writer::write_to_file(const std::experimental::filesystem::path& output_file_name, const Video& output_video) {
    validate_file_extension(output_file_name);

    cv::VideoWriter output_video_stream(
        output_file_name,
        output_video.m_fourcc,
        output_video.m_frame_rate,
        cv::Size(output_video.m_width, output_video.m_height),
        true
    );

    for(int i = 0; i < output_video.m_frame_count; ++i) {
        output_video_stream << output_video.m_frames[i];
    }
}

void Writer::validate_file_extension(const std::experimental::filesystem::path& output_file_name) {
    const auto extension = output_file_name.extension();
    
    /* This list must be updated */
    const std::set<std::experimental::filesystem::path> available_file_extensions {".mp4", ".avi", ".mkv"};
    if(available_file_extensions.find(extension) == available_file_extensions.end()) {
        throw MyException(extension, " is not supported file extension at this moment.");
    }
}