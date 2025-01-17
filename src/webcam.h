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
        std::string command =  "./" + darknet_exe 
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

    
    // Execute the command and capture output
    void executeDemo() const {
        // Change current directory to Darknet directory
        fs::current_path(darknet_dir);

        // Build command
        std::string command = buildCommand();

        std::cout << "\n\nExecuting command " << command << "\n\n";

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


    
};