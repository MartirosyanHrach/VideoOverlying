#ifndef VIDEO_WRITER
#define VIDEO_WRITER
#include <string>
#include "Video.hpp"

/**
 * @brief   This class intends to create video file
 *          and write the specified data to that file.
 */
class Writer {
public:

    /**
     * @brief       Get the file name and overlayed video to write in the file.
     * @param[in]   output_file_name    - Output file name.
     * @param[in]   output_video        - Already overlayed video, which will be written in the file.
     */  
    static void write_to_file(const std::string& output_file_name, const Video& output_video);
    
private:
    /**
     * @brief       Get file extension, to check whether specified extension is supported.
     * @param[in]   outputFileName  - Output file name.
     */  
    static void validate_file_extension(const std::string& output_file_name);
};

#endif // VIDEO_WRITER