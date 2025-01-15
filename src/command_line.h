#pragma once

#include <iostream>
#include <cstdlib>    // For std::system()
#include <filesystem> // For std::filesystem::exists
#include <stdexcept>  // For std::runtime_error
#include <string>
#include <optional>

#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <stdio.h> 

#ifdef _WIN32
    #include <windows.h>
#elif defined(__unix__)  // For Unix-like systems (Linux, BSD, etc.)
    #include <unistd.h>
#elif defined(__APPLE__)  // For macOS systems
    #include <unistd.h>
#elif defined(__POSIX__)  // For POSIX-compliant systems
    #include <unistd.h>
#endif

namespace fs = std::filesystem;


class DarknetCommand {
public:
    DarknetCommand(){}

    virtual void validatePaths() const = 0;
    virtual std::string saveMedia(const std::string& outputData) = 0;
    virtual std::string saveData(const std::string& outputData) = 0;
    virtual std::string setThreshold(const std::string& outputData) = 0;
    virtual std::string buildCommand() const = 0;
    virtual void executeDemo() const = 0;

};


