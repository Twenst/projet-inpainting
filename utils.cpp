#include "utils.h"

double absf(double f)
{
    return (f > 0) ? f : -f;
}

bool selectZone(int& x1, int& y1, int& x2, int& y2)
{
    // demande deux clics gauches, remplit x1, y1, x2 et y2 avec les coordonnées des clics et retourne True
    // En cas de clic droit, retourne False
    
    return(getMouse(x1, y1)==1 and getMouse(x2,y2)==1);
}

void toImageByte(ImgPixel Img, ImgByte Ib)
{
    
}

void computeGradientNormal(double gradient[2], double normal[2], ImgPixel Img, Pixel p, ImgByte ImgB)
{
    
}

double computeData(double gradient[2],double normal[2]) // cd code
{
    double d = gradient[0]*normal[0];
    d += gradient[1]*normal[1];

    return double(absf(d)/256);
}