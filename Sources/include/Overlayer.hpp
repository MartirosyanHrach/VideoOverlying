#ifndef OVERLAYER
#define OVERLAYER

#include <string>
#include "Reader.hpp"
#include "Writer.hpp"
#include "Tracker.hpp"
#include "BackgroundSubtractor.hpp"
#include "MyException.hpp"

class Overlayer {
public:
    Overlayer(const std::string& backgroundVideo, const std::string& movingObjectsVideo, const std::string& outputFileName);

private:

};

#endif //OVERLAYER

Overlayer::Overlayer(const std::string& backgroundVideo, const std::string& movingObjectsVideo, const std::string& outputFileName) {
    Reader movingObjects("/home/hrach/Downloads/termo.mp4");
    Reader backgroundVideo("/home/hrach/Downloads/bozzz.mp4");

}