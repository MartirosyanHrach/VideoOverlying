#include <iostream>
#include "Reader.hpp"
#include "Writer.hpp"
#include "Tracker.hpp"
#include "BackgroundSubtractor.hpp"
#include "Overlayer.hpp"
#include "MyException.hpp"

int main() {
    try{
        
        const std::string backgroundVideo = "/home/hrach/Downloads/background.mp4";
        const std::string movingObjectsVideo = "/home/hrach/Downloads/termo.mp4";
        const std::string outputVideo = "/home/hrach/Downloads/OutputVideo.mp4";

        Overlayer obj(backgroundVideo, movingObjectsVideo, outputVideo);  
        obj.writeToFile();
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
}
