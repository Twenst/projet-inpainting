cmake_minimum_required(VERSION 3.4)
project(Inpainter)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

find_package(Imagine REQUIRED)

add_executable(Inpainter main.cpp
    Pixel.h
    Pixel.cpp
    Patch.h
    Patch.cpp
    Front.h
    Front.cpp
    Image.h
    Image.cpp
    Inpainter.h
    Inpainter.cpp)
ImagineUseModules(Inpainter Graphics)
