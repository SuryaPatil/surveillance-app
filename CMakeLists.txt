cmake_minimum_required(VERSION 3.10)
project(CaptureFrames)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(CaptureFrames main.cpp digitizer.cpp tracker.cpp)
target_link_libraries(CaptureFrames ${OpenCV_LIBS}) 