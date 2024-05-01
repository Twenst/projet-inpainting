#pragma once
#include <Imagine/Graphics.h>
#include "Pixel.h"
#include <Imagine/Images.h>
using namespace Imagine;

typedef Image<Pixel> ImgPixel;
typedef Image<bool> ImgBool;
typedef Image<byte> ImgByte;

/* Methode de la classe
 * I.width()
 * I.height()
 * Pour accéder à un pixel : I(x,y)
 * Pour modifier un pixel : I(x,y)=p;
 * Faire une copie : I.copy();
*/

void display(Imagine::Image<pixel> I, int coeff);                               // Affiche l'image
bool getImage(ImgPixel& I, std::string imageLink, int argc, char* argv[]);      // Obtention de l'image à partir d'un fichier
