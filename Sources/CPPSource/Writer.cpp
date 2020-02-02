#include "Writer.hpp"

Writer::Writer(const std::string& outputFileName, int fourcc, double fps, int width, int height) :
    m_outputFileName(outputFileName),
    m_fourcc(fourcc),
    m_fps(fps),
    m_size(width, height) {}

Writer::Writer(const std::string& outputFileName, const std::string& codec, double fps, int width, int height) :
    m_outputFileName(outputFileName),
    m_fps(fps),
    m_size(width, height) {
        m_fourcc = getFourcc(outputFileName, codec);
}

void Writer::writeToFile(const std::vector<cv::Mat>& videoFrames) {
    cv::VideoWriter outputVideo(m_outputFileName, m_fourcc, m_fps, m_size, true);
    
    for(size_t i = 0; i < videoFrames.size(); ++i) {
        outputVideo << videoFrames[i];
    }
}

std::string Writer::getFileExtension(const std::string& fileName) {
    auto found = fileName.find_last_of('.');
    return fileName.substr(found + 1);
}

int Writer::getFourcc(const std::string& outputFileName, const std::string& codec) {
    std::string extension = getFileExtension(outputFileName);
    
    std::map<std::string, std::set<std::string>> availableCodecsAndExtensions{
        {"mp4", {"MJPG", "MJ2C", "VP80", "HEVC", "X264", "MPEG4"}},
        {"avi", {"XviD", "ASV1", "ASV2", "FFV1", "MJPG", "HFYU", "MJ2C", "VP80", "SVQ1", "WMV1", "WMV2", "ZLIB", "MPEG4"}},
        {"mkv", {"HEVC", "XviD", "ASV1", "ASV2", "MJ2C", "WMV1", "WMV2", "ZLIB", "MJPG", "VP80", "MPEG4"}}
    };

    auto findExtension = availableCodecsAndExtensions.find(extension);
    if(findExtension == availableCodecsAndExtensions.end()) {
        throw MyException(extension, "is unsupported file extension, please see ReadMe.md");
    }

    auto findCodec = availableCodecsAndExtensions[extension].find(codec);
    if(findCodec ==  availableCodecsAndExtensions[extension].end()) {
        throw MyException(codec, "is unsupported codec format.");
    }

    return  cv::VideoWriter::fourcc((*findCodec)[0], (*findCodec)[1], (*findCodec)[2], (*findCodec)[3]); 
}