cmake_minimum_required(VERSION 2.8.4)
project(gfttscore)

## Compile as C++14
set(CMAKE_CXX_STANDARD 14)
if (NOT CMAKE_BUILD_TYPE)
    # Options: Debug, Release, MinSizeRel, RelWithDebInfo
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "No build type selected, default to ${CMAKE_BUILD_TYPE}")
endif()


# Find dependent libraries
find_package(OpenCV 3 REQUIRED)
message(STATUS "OpenCV Version: " ${OpenCV_VERSION})

# Include header files
include_directories(include ${OpenCV_INCLUDE_DIRS})

# Create the executables and link them to libs
add_executable(main src/main.cpp src/cvmodified.cpp)
target_link_libraries(main ${OpenCV_LIBS})