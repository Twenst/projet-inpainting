#include "Front.h"
#include <cmath>
using namespace std;

// Les pixels de la frontiere sont REMPLIS ie. getFilled est vrai, sinon c'est l'intérieur de la frontiere

bool has_unfilled_neighbor(const ImgPixel& Img, Pixel p)
{
    int w = Img.width(), h = Img.height();
    int x = p.getX(), y = p.getY();

    if (x < w and not Img(x+1,y).getFilled())
        return true;
    if (y < h and not Img(x,y+1).getFilled())
        return true;
    if (y > 0 and not Img(x,y-1).getFilled())
        return true;
    if (x > 0 and not Img(x-1,y).getFilled())
        return true;

    return false;
}

bool is_within_square(Pixel p, Pixel c1, Pixel c2) // si p est dans le rectangle défini par c1 et c2
{
    int x = p.getX(), y = p.getY();
    return (min(c1.getX(),c2.getX())<=x<=max(c1.getX(),c2.getX()) and min(c1.getY(),c2.getY())<=y<=max(c1.getY(),c2.getY()));
}

Front::Front()
{
}

Front::Front(list<Pixel> pxs)
{
    pixels=pxs;
}

void Front::defineFront(const ImgPixel& Img, Pixel p1, Pixel p2) // ajoute le rectange défini par p1 et p2
{
    list<Pixel> l_front;
    update_list(l_front,p1,p2);

    list<Pixel>::iterator iter = pixels.end();

    for (list<Pixel>::iterator i = l_front.begin(); i != l_front.end(); ++i)
        if (i->getFilled())
            pixels.insert(iter,*i);
}

void Front::defineFront(const ImgPixel& Img, std::list<Pixel> front_pixels)
{
    list<Pixel>::iterator iter = pixels.end();

    for (list<Pixel>::iterator i = front_pixels.begin(); i != front_pixels.end(); ++i)
        if (i->getFilled())
            pixels.insert(iter,*i);
}

/*void Front::updateFront(const ImgPixel& Img, list<Pixel> patch_pixels) 
// on doit m-a-j la frontiere en sachant qu'on vient d'ajouter le patch dont les bords sont dans patch_pixels 
{
    for (list<Pixel>::iterator i = pixels.begin(); i != pixels.end(); ++i)
    {

    }

    list<Pixel>::iterator iter = pixels.end();

    for (list<Pixel>::iterator i = patch_pixels.begin(); i != patch_pixels.end(); ++i)
        if (i->getFilled())
            pixels.insert(iter,*i); 
}*/

void Front::updateFront(const ImgPixel& Img, Pixel p1, Pixel p2) // maj de la frontiere apres ajout du patch défini par p1 et p2
{
    list<Pixel> l_patch;
    update_list(l_patch,p1,p2);

    // On enlève tous les points de la frontière actuelle qui sont dans le patch
    for (list<Pixel>::iterator i = pixels.begin(); i != pixels.end();)
    {
        if (is_within_square(*i,p1,p2)) // à enlever
        {
            pixels.erase(i);
        }
        else ++i;
    }

    // On maj la nouvelle bordure de la frontiere au niveau du patch
    for (list<Pixel>::iterator i = l_patch.begin(); i != l_patch.end(); ++i)
    {
        if (has_unfilled_neighbor(Img, *i))
        {
            pixels.push_back(*i);
        }
    }
}

void Front::clearSides(const ImgPixel& Img) //enleve les pixels de la frontiere qui sont sur le bord de l'image
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

void update_list(std::list<Pixel>& l, int x1, int y1, int x2, int y2)
{
    // Ajouter les points entre (x1,y1) et (x2,y1), entre (x2,y1) et (x2,y2), 
    // entre (x2,y2) et (x1,y2) et entre (x1,y2) et (x1,y1).

    // Ajoute les bords
    for (int i = min(x1,x2); i <= max(x1,x2); i++) // y1 et y2
    {
        l.push_front(Pixel(i,y1));
        l.push_front(Pixel(i,y2));
    }
    for (int j = min(y1,y2)+1; j < max(y1,y2); j++) // x1 et x2
    // ici on ne met pas les coins afin qu'ils ne soient pas en double
    {
        l.push_front(Pixel(x1,j));
        l.push_front(Pixel(x2,j));
    }
}

void update_list(std::list<Pixel>& l, Pixel p1, Pixel p2)
{
    int x1 = p1.getX(), y1 = p1.getY();
    int x2 = p2.getX(), y2 = p2.getY();

    update_list(l,x1,y1,x2,y2);
}

