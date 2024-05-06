#pragma once
#include "Inpainter.h"

Inpainter::Inpainter(){
}

Inpainter::Inpainter(ImgPixel Img, Front fr){
    image=Img;
    frontier=fr;
}

