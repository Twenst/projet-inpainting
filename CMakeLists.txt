cmake_minimum_required(VERSION 3.5)
project(Inpainting)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
set(CMAKE_CXX_STANDARD 11)

find_package(Imagine REQUIRED COMPONENTS Images)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Inpainting main.cpp
                          utils.h utils.cpp
                          Inpainter.h Inpainter.cpp)

target_link_libraries(Inpainting Imagine::Images ${OpenCV_LIBS})