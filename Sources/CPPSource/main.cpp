#include "opencv2/opencv.hpp"
#include <iostream>
#include "Reader.hpp"
#include "Writer.hpp"
#include "Tracker.hpp"
#include "MyException.hpp"
#include "BackgroundSubtractor.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

int main() {
    try{
        Reader movingVideo("/home/hrach/Downloads/termo.mp4");
        Reader backgroundVideo("/home/hrach/Downloads/bozzz.mp4");
        Tracker t(movingVideo, "TLD");
        BackgroundSubtractor  background(backgroundVideo, "mog2");

        auto back = background.getBackground(); //Background video.
        auto moving = movingVideo.getVideoFrames();
        auto mask = t.getMasks();
        auto size = std::min(mask.size(), back.size());

        cv::Mat temp1;
        cv::Mat temp2;
        cv::Mat maskInv;
        std::vector<cv::Mat> output(size);
    
        for(size_t i = 0; i < size; ++i) {
            cv::bitwise_not(mask[i], maskInv);
            temp1 = moving[i];
            temp1.setTo(0, maskInv);
            temp2 = back[i];
            temp2.setTo(0, mask[i]);
            output.emplace_back(temp1 + temp2);
        }

        Writer w("/home/hrach/Desktop/testCV/build/boz.mp4", movingVideo.getCodecNumber(), movingVideo.getFrameRate(), movingVideo.getWidth(), movingVideo.getHeight());
        w.writeToFile(output);
    }
    catch(MyException& e) {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    catch(...) {

    }
}
