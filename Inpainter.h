#pragma once
#include "Image.h"
#include "Pixel.h"
#include "Patch.h"
#include "Front.h"
#include "utils.h"

/* La classe Inpainter permet de réunir les deux éléments centraux de l'algorithme : la frontière et l'image.
 */

class Inpainter 
{
    public:
    ImgPixel image;
    Front frontier;
    int patch_size;
    Inpainter();
    Inpainter(ImgPixel Img, Front fr, int ps);
    void place_patch(Patch psi_q, Loc crds_p);      // Copie le patch \psi_q sur les pixels non remplis du patch \psi_p
                                                    // et affecte aux pixels non remplis du patch \psi_p la valeur de Confidence du pixel p_max
};
