#pragma once

#include <string>

namespace path{

    std::string root = "/home/autonomy/Dev/darknet-YOLOv4-cpp/";  // adjust root accordingly
    std::string darknet_dir     = "/home/autonomy/Dev/darknet/";      // adjust darknet directory accordingly
    std::string darknet_exe     = "darknet";
    std::string data_path       = root + "config/coco.data";
    std::string config_path     = root + "config/yolov4.cfg";
    std::string weights_path    = root + "weights/yolov4.weights";

}