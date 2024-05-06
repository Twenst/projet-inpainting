#pragma once
#include "Image.h"
#include "Pixel.h"
#include "Patch.h"
#include "Front.h"
#include "utils.h"



class Inpainter 
{
    public:
    ImgPixel image;
    Front frontier;
    int patch_size;
    Inpainter();
    Inpainter(ImgPixel Img, Front fr);
    void place_patch(Patch psi_q, Pixel p); // copie le patch psi_q sur p, gere tout
};
