#pragma once
#include "Image.h"
#include "Pixel.h"
#include "Patch.h"
#include "Front.h"

#include <Imagine/Images.h>
using namespace Imagine;


bool selectZone(int& x1,int& y1,int& x2,int& y2);           // Permet de sélectionner un rectangle sur l'image
void toImageByte(ImgPixel Img, ImgByte Ib);
void computeGradientNormal(double gradient[2], double normal[2], ImgPixel Img, Pixel p, ImgByte ImgB);    // Calcule le gradient et le vecteur normal au pixel p
void computeGradientNormalUsingByte(double gradient[2], double normal[2], ImgPixel Img, Pixel p, ImgByte ImgB);
//void computeGradientNormalUsingColor(double gradient[2], double normal[2], ImgPixel Img, Pixel p, ImgByte ImgB);
double computeData(double gradient[2],double normal[2]);                                                  // Calcule le terme de donnée à partir du gradient et de la normale
void set_filled(ImgPixel Img, Pixel p1, Pixel p2);
