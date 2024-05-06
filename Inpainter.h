#pragma once
#include "Image.h"
#include "Pixel.h"
#include "Patch.h"
#include "Front.h"
#include "utils.h"

class Inpainter {
    ImgPixel image;
    Front frontier;
public:
    Inpainter();
    Inpainter(ImgPixel Img, Front fr);
};
