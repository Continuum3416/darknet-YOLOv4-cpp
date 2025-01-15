#pragma once
#include "command_line.h"


class DarknetWebcam : public DarknetCommand {
private:
    std::string darknet_dir;      // Darknet root directory
    std::string darknet_exe;      // Darknet executable name
    std::string data_path;        // Path to data file
    std::string config_path;      // Path to config file
    std::string weights_path;     // Path to weights file

    std::optional<std::string> data_output_file; // Optional output file path
    std::optional<std::string> video_output_file;
    std::optional<std::string> threshold;


public:
    // Constructor to initialize paths
    DarknetWebcam(const std::string& darknetDir, const std::string& exeName,
                  const std::string& dataFile, const std::string& configFile, 
                  const std::string& weightsFile)
        :   darknet_dir(darknetDir), 
            darknet_exe(exeName),
            data_path(dataFile), 
            config_path(configFile), 
            weights_path(weightsFile) {}

    // Method to validate paths
    void validatePaths() const override{
        if (!fs::exists(darknet_dir)) {
            throw std::runtime_error("Darknet directory does not exist: " + darknet_dir);
        }
        if (!fs::exists(fs::path(darknet_dir) / darknet_exe)) {
            throw std::runtime_error("Darknet executable not found in directory: " + darknet_exe);
        }
        if (!fs::exists(data_path)) {
            throw std::runtime_error("Data file not found: " + data_path);
        }
        if (!fs::exists(config_path)) {
            throw std::runtime_error("Config file not found: " + config_path);
        }
        if (!fs::exists(weights_path)) {
            throw std::runtime_error("Weights file not found: " + weights_path);
        }
    }

    std::string saveMedia(const std::string& outputData) override{
        video_output_file = outputData;
        return outputData;
    }

    std::string saveData(const std::string& outputData) override{
        data_output_file = outputData;
        return outputData;
    }

    std::string setThreshold(const std::string& outputData) override{
        threshold = outputData;
        return outputData;
    }
    
    // Method to build the command string
    std::string buildCommand() const override{
        std::string command = darknet_exe 
            + " detector demo \"" 
            + data_path + "\" \"" 
            + config_path + "\" \"" 
            + weights_path + "\"";

        if (video_output_file) {
            command += " -out_filename \"" + *video_output_file + "\"";
        }

        if (threshold) {
            command += " -thresh " + *threshold;
        }

        if (data_output_file) {
            command += " > \"" + *data_output_file + "\"";
        }

        return command;
    }

    // void executeDemo() const{
    //     // Change current directory to Darknet directory
    //     fs::current_path(darknet_dir);

    //     // Build command
    //     std::string command = buildCommand();

    //     // Execute the command and check the result
    //     int result = std::system(command.c_str());
    //     if (result != 0) {
    //         throw std::runtime_error("Darknet demo execution failed with code " + std::to_string(result));
    //     }

    //     std::cout << "Darknet demo executed successfully.";

    //     // Open output file for writing the coordinates (to the specified directory)
    //     std::string outputDir = "D:/./C.S_Docs_and_Projects_C++/YOLO/darknet_test/src/";
    //     std::string outputFile = outputDir + "bounding_boxes.txt";
    //     std::ofstream out(outputFile);

    //     if (!out) {
    //         throw std::runtime_error("Failed to open output file for writing: " + outputFile);
    //     }

    //     // Load the output file that contains bounding box data (if redirected to a file)
    //     if (data_output_file) {
    //         std::ifstream outputFileStream(*data_output_file);
    //         std::string line;
    //         while (std::getline(outputFileStream, line)) {
    //             // Parse the output to get bounding boxes
    //             std::istringstream iss(line);
    //             float x, y, w, h;
    //             int class_id;
    //             float confidence;

    //             // Parse bounding box coordinates and class info
    //             if (iss >> class_id >> confidence >> x >> y >> w >> h) {
    //                 // Write bounding box data to the output file
    //                 out << "Class: " << class_id << ", Confidence: " << confidence << "\n";
    //                 out << "Bounding Box: x=" << x << ", y=" << y << ", w=" << w << ", h=" << h << "\n\n";

    //                 // Optionally, print to console as well
    //                 std::cout << "Class: " << class_id << ", Confidence: " << confidence << "\n";
    //                 std::cout << "Bounding Box: x=" << x << ", y=" << y << ", w=" << w << ", h=" << h << "\n";
    //             }
    //         }
    //     }

    //     // Close the output file after writing
    //     out.close();

    //     std::cout << "Bounding box coordinates saved to: " << outputFile << std::endl;
    // }

    
    // Execute the command and capture output
    void executeDemo() const {
        // Change current directory to Darknet directory
        fs::current_path(darknet_dir);

        // Build command
        std::string command = buildCommand();

        //std::cout << "\n\nExecuting command " << command << "\n\n";

        // Execute the command and check the result
        int result = std::system(command.c_str());
        if (result != 0) {
            throw std::runtime_error("Darknet demo execution failed with code " + std::to_string(result));
        }

        std::cout << "Darknet demo executed successfully.";
        if (video_output_file) {
            std::cout << "Video will be saved to: " << *video_output_file << std::endl;
        }
        if (threshold) {
            std::cout << "Threshold set to: " << *threshold << std::endl;
        }
        if (data_output_file) {
            std::cout << "Console output will be saved to: " << *data_output_file << std::endl;
        }
        std::cout << std::endl; 


    }


    

 
    void executeDemo_() const {
        char buffer[MAX_PATH];
        if (GetCurrentDirectoryA(MAX_PATH, buffer)) {
            std::cout << "Current working directory: " << buffer << std::endl;
        }
        fs::current_path(darknet_dir);

        // Build command
        std::string command = buildCommand();

        // Execute the command and capture the output
#ifdef _WIN32
        FILE* pipe = _popen(command.c_str(), "r");
#elif defined(__unix__) 
        FILE* pipe = popen(command.c_str(), "r");
#endif
        if (!pipe) {
            throw std::runtime_error("Darknet demo execution failed");
        }

        // Read the output line by line
        buffer[128];
        std::string output;
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            output += buffer;
        }
        fclose(pipe);

        // Parse the output for coordinates of bounding boxes
        std::istringstream iss(output);
        std::string line;
        std::vector<std::tuple<int, float, float, float, float, float>> boxes; // (class_index, confidence, x, y, width, height)

        while (std::getline(iss, line)) {
            // Check if the line contains a detection
            if (line.find("left") != std::string::npos) {
                int class_index;
                float confidence, x, y, width, height;
                std::istringstream line_stream(line);

                // Example: left: 63, top: 50, right: 150, bottom: 200
                // Format: x, y, width, height
                line_stream >> class_index >> confidence >> x >> y >> width >> height;

                // Store the detection information
                auto t = std::make_tuple(class_index, confidence, x, y, width, height);
                boxes.push_back(t);
            }
        }

        // Open a log file to save coordinates
        std::ofstream log_file("detection_log.txt", std::ios::out | std::ios::app); // Open file in append mode
        if (!log_file.is_open()) {
            throw std::runtime_error("Unable to open log file");
        }


        for (const auto& box : boxes) {
            int class_index;
            float confidence, x, y, width, height;
            std::tie(class_index, confidence, x, y, width, height) = box;

            log_file << "Detected object: Class " << class_index
                    << ", Confidence: " << confidence
                    << ", Coordinates: (x: " << x << ", y: " << y
                    << ", width: " << width << ", height: " << height << ")\n";
        }

        log_file << "----------------------------------------\n";

        // Close the log file
        log_file.close();

        std::cout << "Darknet demo executed successfully.\n";
        if (video_output_file) {
            std::cout << "Video will be saved to: " << *video_output_file << std::endl;
        }
        if (threshold) {
            std::cout << "Threshold set to: " << *threshold << std::endl;
        }
        if (data_output_file) {
            std::cout << "Console output will be saved to: " << *data_output_file << std::endl;
        }
        std::cout << std::endl;
    }
};