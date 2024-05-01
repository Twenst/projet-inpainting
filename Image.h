#pragma once
#include <Imagine/Graphics.h>
#include "Pixel.h"
#include <Imagine/Images.h>
using namespace Imagine;

typedef Image<Pixel> ImgPixel;
typedef Image<bool> ImgBool;

// On utilise le type Imagine::Image<AlphaColor>
/* Methode de la classe
 * I.weight()
 * I.height()
 * Pour accéder à un pixel : I(x,y)
 * Pour modifier un pixel : I(x,y)=p;
 * Faire une copie : I.copy();
*/

void affiche(Imagine::Image<pixel> I, int coeff);
bool getImage(ImgPixel& I, std::string imageLink, int argc, char* argv[]);
