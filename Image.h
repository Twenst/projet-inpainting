#pragma once
#include "Pixel.h"
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace Imagine;

typedef Image<Pixel> ImgPixel;
typedef Image<bool> ImgBool;
typedef Image<byte> ImgByte;

void display(ImgPixel Img, int coeff);                                          // Affiche l'image
bool getImage(ImgPixel& I, std::string imageLink, int argc, char* argv[]);      // Obtention de l'image à partir d'un fichier
void eraseZone(ImgPixel& Img, Pixel p1, Pixel p2);
