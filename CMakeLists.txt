cmake_minimum_required(VERSION 3.5)
project(Inpainter)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
set(CMAKE_CXX_STANDARD 11)
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
    Inpainter.cpp
    utils.h
    utils.cpp
    Loc.h
    Loc.cpp)
ImagineUseModules(Inpainter Graphics)
