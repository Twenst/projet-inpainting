#pragma once
#include "Pixel.h"
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace Imagine;

/* L'image de nous manipulons est une Image de Pixel (de type ImgPixel)
 */

typedef Image<Pixel> ImgPixel;
typedef Image<bool> ImgBool;
typedef Image<byte> ImgByte;

void display(ImgPixel Img, int coeff);                                          // Affiche l'image
bool getImage(ImgPixel& I, std::string imageLink, int argc, char* argv[]);      // Transpose les informations de l'image obtenue à partir d'un fichier dans l'image de type ImgPixel
void eraseZone(ImgPixel& Img, Loc crds1, Loc crds2);                            // Supprime (met les pixels en couleur BLANC et en "non remplis") sur la zone délimitée par crds1 et crds2
