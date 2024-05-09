#pragma once
#include "Image.h"
#include "Pixel.h"
#include "Patch.h"
#include "Front.h"
#include <Imagine/Images.h>
using namespace Imagine;

/* Cette classe permet de donner certains outils étant utiles
 * pour réaliser les méthodes des autres classes.
 */

bool selectZone(int& x1,int& y1,int& x2,int& y2);                                                           // Permet de sélectionner un rectangle sur l'image
void toImageByte(ImgPixel Img, ImgByte Ib);                                                                 // Transforme l'image en nuance de gris (utile pour calculer le gradient)
void computeGradientNormal(double gradient[2], double normal[2], ImgPixel Img, Loc crds_p, ImgByte ImgB);   // Calcule le gradient et le vecteur normal au pixel de coordonnées crds_p
double computeData(double gradient[2],double normal[2]);                                                    // Calcule le terme de donnée à partir du gradient et de la normale

