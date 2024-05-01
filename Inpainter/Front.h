#pragma once
#include "Image.h"
#include "Pixel.h"
#include "Patch.h"

class Front {
    std::list<Pixel> pixels;
public:
    Front();
    Front(std::list<Pixel> pxs);
    void define_front(const ImgBool& ImgB);
};
