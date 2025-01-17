#include <iostream>
#include <string>
//#include <opencv2/opencv.hpp>
#include "global_path.h"
#include "webcam.h"



int main() {
    try {
        std::string data_output_path = "/home/autonomy/Dev/darknet-YOLOv4-cpp/output/webcam_output.log"; 
        std::string video_output_path = "/home/autonomy/Dev/darknet-YOLOv4-cpp/media/output.mp4";
        std::string threshold = "0.24";

        std::cout << path::data_path << std::endl;

        DarknetWebcam darknet(  path::darknet_dir,
                                path::darknet_exe,
                                path::data_path,
                                path::config_path,
                                path::weights_path);

        
        //darknet.validatePaths();

        // order doesn't matter as long as they're before executeDemo()
        darknet.saveMedia(video_output_path);
        darknet.saveData(data_output_path);
        darknet.setThreshold(threshold);

        darknet.executeDemo();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}



// Run: cd src; g++ -std=c++17 webcam.cpp -o ./bin/webcam.exe; ./bin/webcam.exe

// Linux: g++ -std=c++17 webcam.cpp -o ./bin/webcam; ./bin/webcam

// cmake --build .\build\ --config Debug; .\build\Debug\webcam.exe