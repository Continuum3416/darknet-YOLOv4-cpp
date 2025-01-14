cmake_minimum_required(VERSION 3.10)

# Set project name
project(MyYOLOProject)

# Define the C++ standard 
set(CMAKE_CXX_STANDARD 17)

# Define YOLO project source and directories
set(DARKNET_DIR "C:/Libraries/YOLO/darknet-master")

# Gather all .cpp files from the source directory
file(GLOB SOURCES "source/*.cpp")

# Add additional source files from the Darknet source directory
file(GLOB DARKNET_SOURCES "${DARKNET_DIR}/src/*.c") # Darknet source files are in C, so use *.c

# Combine user sources with Darknet sources
list(APPEND SOURCES ${DARKNET_SOURCES})

# Set OpenCV path
set(OpenCV_DIR "C:/Libraries/OpenCV/build") 

# Add OpenCV and CUDA paths (if needed)
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR})
find_package(CUDA REQUIRED)

# Include directories for Darknet, OpenCV, and Pthreads
include_directories(${DARKNET_DIR}/include)
include_directories(${DARKNET_DIR}/src)               # Include Darknet source directory
include_directories(${DARKNET_DIR}/3rdparty/pthreads/include)  # Add Pthreads include directory
include_directories(${OpenCV_INCLUDE_DIRS})

# Link directories for Pthreads, Darknet, and OpenCV
link_directories(${DARKNET_DIR}/3rdparty/pthreads/bin)  # Add Pthreads lib directory
link_directories(${DARKNET_DIR}/lib)                   # Add Darknet lib directory
link_directories(${OpenCV_LIB_DIR})

# Create executable for each source file
foreach(SOURCE_FILE ${SOURCES})
    # Extract the base name (without extension) to use as the target name
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)
    
    # Create an executable for each source file
    add_executable(${TARGET_NAME} ${SOURCE_FILE})

    # Link libraries: Darknet, OpenCV, Pthreads, and CUDA
    target_link_libraries(${TARGET_NAME} 
        ${DARKNET_DIR}/libdarknet.a  # or libdarknet.so, depending on your setup
        pthreadVC2                  # Link Pthreads library
        ${OpenCV_LIBS}
        ${CUDA_LIBRARIES}           # If CUDA is used
    )
endforeach()
