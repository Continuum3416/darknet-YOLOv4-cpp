#include <iostream>
#include <string>
//#include <opencv2/opencv.hpp>
#include "global_path.h"
#include "command_line.h"



int main() {
    try {
        std::string data_output_path = "D:/.C.S_Docs_and_Projects_C++/YOLO/darknet_test/output/webcam_output.log"; 
        std::string video_output_path = "D:/.C.S_Docs_and_Projects_C++/YOLO/darknet_test/media/output.mp4";
        std::string threshold = "0.24";
        DarknetWebcam darknet(  path::darknet_dir,
                                path::darknet_exe,
                                path::data_path,
                                path::config_path,
                                path::weights_path);

        
        darknet.validatePaths();

        // order doesn't matter as long as they're before executeDemo()
        darknet.saveVideo(video_output_path);
        darknet.saveData(data_output_path);
        darknet.setThreshold(threshold);

        darknet.executeDemo();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}



// Run: g++ webcam.cpp -o ./bin/webcam.exe; ./bin/webcam.exe

// cmake --build .\build\ --config Debug; .\build\Debug\webcam.exe