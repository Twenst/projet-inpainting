#pragma once
#include "Pixel.h"
#include "Image.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

class Patch {
    Pixel center;    // centre du patch
    int size;      // taille du patch

public :
    Patch();
    Patch(Pixel c,int s);
    Patch(const Patch & ptch);
    Pixel getCenter() const ;
    int getSize() const ;
    void setCenter(Pixel c);
    void setSize(int s);
    void set_filled(ImgPixel& Img);
};

int distPatch(const Pixel& q, const Patch& psi_p, const ImgPixel& I);  // Calcul la similarité (=distance euclidienne) entre le patch de frontière psi_p et la patch psi_q
int argMinDistPatch(Patch& psi_q, const Patch& psi_p, const ImgPixel& I);  // Modifie psi_q tel qu'il soit le patch le plus similaire à psi_p
