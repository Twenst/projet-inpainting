#include "Front.h"
#include <cmath>
using namespace std;

Front::Front()
{
}

Front::Front(list<Pixel> pxs)
{
    pixels=pxs;
}

void Front::defineFront(const ImgPixel& Img, list<Pixel> list_pixels)
{
    int w = Img.width(), h = Img.height();

    list<Pixel>::iterator iter = pixels.end();

    for (list<Pixel>::iterator i = list_pixels.begin(); i != list_pixels.end(); ++i)
        if (i->getFilled())
            pixels.insert(iter,*i);
}

void Front::updateFront(const ImgPixel& Img, list<Pixel> list_pixels)
{
    // demander à Felix la diff entre define et update
}

void Front::clearSides(const ImgPixel& Img)
{
    int w = Img.width(), h = Img.height();

    for (list<Pixel>::iterator i = pixels.begin(); i != pixels.end(); ++i)
    {
        int x = i->getX(), y = i->getY();
        if (x == 0 or y == 0 or x >= w-1 or y >= h-1)
        {
            pixels.remove(*i);
        }
    }
}

Pixel Front::pixelMaxPriority() // on peut pas mettre cette fonction en const à cause de l'iterator
{
    Pixel p_max = pixels.front();
    
    for (list<Pixel>::iterator i = pixels.begin(); i != pixels.end(); ++i)
    {
        if (p_max.getPriority() < i->getPriority())
        {
            p_max = *i;
        }
    }
    return p_max;
} 

void Front::updateData(ImgPixel& Img)
{

}

bool Front::isEmpty()
{
    return pixels.empty();
}

void Front::display()
{
    for (list<Pixel>::iterator i = pixels.begin(); i != pixels.end(); ++i)
    {
        drawPoint(i->getX(), i->getY(), BLACK);
    }
}

bool selectZone(int& x1,int& y1,int& x2,int& y2)
{
    return(getMouse(x1, y1)==1 && getMouse(x2,y2)==1);
    /* demande deux clics gauches, remplit x1, y1, x2 et y2 avec les coordonnées des clics et retourne True
     * En cas de clic droit, retourne False
     */
}
