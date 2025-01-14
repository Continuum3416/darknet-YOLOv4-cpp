#include <iostream>

// Include Darknet headers wrapped in extern "C"
extern "C" {
#include "darknet.h"
}

int main() {
    // Initialize Darknet
    std::cout << "Initializing Darknet..." << std::endl;

    // Load the network configuration
    const char *cfg_file = "config/yolov4.cfg";
    const char *weights_file = "weights/yolov4.weights";


    network *net = load_network_custom((char *)cfg_file, (char *)weights_file, 1, 1);
    if (!net) {
        std::cerr << "Failed to load the network!" << std::endl;
        return -1;
    }
    set_batch_network(net, 1); // Set batch size
    std::cout << "Network loaded successfully!" << std::endl;

    // Load an image
    const char *image_path = "data/dog.jpg";
    image im = load_image_color((char *)image_path, 0, 0);
    if (!im.data) {
        std::cerr << "Failed to load image!" << std::endl;
        free_network_ptr(net);
        return -1;
    }
    std::cout << "Image loaded successfully!" << std::endl;

    // Perform detection
    float *predictions = network_predict_ptr(net, im.data);
    std::cout << "Inference completed!" << std::endl;

    // Get bounding boxes and display results
    int nboxes = 0;
    float thresh = 0.5; // Detection threshold
    float hier_thresh = 0.5;
    int *map = 0;       // No mapping needed
    int relative = 0;   // Use absolute coordinates for bounding boxes
    int letter = 0;     // No letterboxing

    // Allocate memory for the number of detections
    detection *dets = get_network_boxes(net, im.w, im.h, thresh, hier_thresh, map, relative, &nboxes, letter);


    std::cout << "Detections: " << nboxes << std::endl;

    for (int i = 0; i < nboxes; ++i) {
        for (int j = 0; j < dets[i].classes; ++j) {
            if (dets[i].prob[j] > thresh) {
                std::cout << "Class " << j << " detected with probability " << dets[i].prob[j] << std::endl;
            }
        }
    }

    // Free memory
    free_detections(dets, nboxes);
    free_image(im);
    free_network_ptr(net);

    std::cout << "Done!" << std::endl;
    return 0;
}



// cmake --build .\build\ --config Debug; .\build\Debug\*.exe

