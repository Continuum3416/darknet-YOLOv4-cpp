#pragma once

#include <string>

namespace path{

    std::string root = "D:/.C.S_Docs_and_Projects_C++/YOLO/darknet_test/";  // adjust root accordingly
    std::string darknet_dir     = "C:/Libraries/YOLO/darknet-master/";      // adjust darknet directory accordingly
    std::string darknet_exe     = "darknet.exe";
    std::string data_path       = root + "config/coco.data";
    std::string config_path     = root + "config/yolov4.cfg";
    std::string weights_path    = root + "weights/yolov4.weights";


}