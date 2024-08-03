cmake_minimum_required(VERSION 3.10)
project(CaptureFrames)
set(OpenCV_DIR ~/opencv_build/opencv)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find and include CURL
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_executable(CaptureFrames src/main.cpp src/digitizer.cpp src/tracker.cpp src/alarm.cpp src/twilio.cpp src/cpp_demo.cpp)
target_link_libraries(CaptureFrames ${OpenCV_LIBS} CURL::libcurl)
