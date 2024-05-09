#include "Front.h"
#include <algorithm>
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
    return (std::min(c1.getX(),c2.getX())<=x<=std::max(c1.getX(),c2.getX()) and std::min(c1.getY(),c2.getY())<=y<=std::max(c1.getY(),c2.getY()));
}

Front::Front()
{
}

Front::Front(list<Pixel> pxs)
{
    pixels=pxs;
}

/* Front::Front(const Front & frt)
{
    pixels = frt.pixels;
} */

void Front::defineFront(ImgPixel& Img, Pixel p1, Pixel p2) // ajoute le rectange défini par p1 et p2
{
    list<Pixel> l_front;
    update_list(Img,l_front,p1,p2);

    list<Pixel>::iterator iter = pixels.end();

    for (list<Pixel>::iterator i = l_front.begin(); i != l_front.end(); ++i)
        if (i->getFilled())
            pixels.push_back(*i);   //pixels.insert(iter,*i);

    eraseZone(Img, p1, p2);

    for (list<Pixel>::iterator it = pixels.begin(); it != pixels.end();){
        if(!Img((*it).getX(),(*it).getY()).getFilled()){
            it = pixels.erase(it);
        }
        else{
            ++it;
        }
    }

}

void Front::defineFront(ImgPixel& Img, std::list<Pixel> front_pixels)
{
    list<Pixel>::iterator iter = pixels.end();

    for (list<Pixel>::iterator i = front_pixels.begin(); i != front_pixels.end(); ++i)
        if (i->getFilled())
            pixels.insert(iter,*i);
}

void Front::updateFront(const ImgPixel& Img, Patch p)
// maj de la frontiere apres ajout du patch défini par p1 et p2
{
    //p.set_filled(Img);
    Pixel centre = p.getCenter(); int n = p.getSize();
    int x = centre.getX(), y = centre.getY();

    Pixel p1(x-n,y-n); Pixel p2(x+n,y+n);

    list<Pixel> l_patch;
    update_list(Img,l_patch,p1,p2);

    // On enlève tous les points de la frontière actuelle qui sont dans le patch
//    for (list<Pixel>::iterator i = pixels.begin(); i != pixels.end();)
//    {
//        if (is_within_square(*i,p1,p2)) // à enlever
//        {
//            pixels.erase(i);
//        }
//        else ++i;
//    }


    for(list<Pixel>::iterator it = pixels.begin(); it != pixels.end();){
        if(((*it).getX()>x-n) && ((*it).getX()<x+n) && ((*it).getY()>y-n) && ((*it).getY()<y+n)) {
            it = pixels.erase(it);
        }
        else{
            ++it;
        }
    }


    // On maj la nouvelle bordure de la frontiere au niveau du patch
    for (list<Pixel>::iterator i = l_patch.begin(); i != l_patch.end(); ++i)
    {
        if (has_unfilled_neighbor(Img, *i)) //has_unfilled_neighbor(Img, *i)
        {
            pixels.push_back(*i);
        }
    }
}

void Front::updateFront(const ImgPixel& Img, Pixel p1, Pixel p2)
// maj de la frontiere apres ajout du patch défini par p1 et p2
{
    //set_filled(Img, p1, p2);

    list<Pixel> l_patch;
    update_list(Img,l_patch,p1,p2);

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

Pixel Front::pixelMaxPriority(const ImgPixel& Img) // on peut pas mettre cette fonction en const à cause de l'iterator
{
    Pixel p_max = pixels.front();
    
    for (list<Pixel>::iterator i = pixels.begin(); i != pixels.end(); ++i)
    {
        if (Img(p_max.getX(),p_max.getY()).getPriority() < Img((*i).getX(),(*i).getY()).getPriority())
        {
            p_max = *i;
        }
    }
    return Img(p_max.getX(),p_max.getY());
} 

void Front::updateData(ImgPixel& Img)
{
    int w = Img.width(), h = Img.height();
    
    double grad[2]; double normal[2];
    ImgByte Ibyte(w,h);
    toImageByte(Img,Ibyte);

    for (list<Pixel>::iterator i = pixels.begin(); i != pixels.end(); ++i)
    {
        computeGradientNormal(grad,normal,Img,*i,Ibyte);
        Img(i->getX(),i->getY()).setData(computeData(grad, normal)); // cf formule
        //i->setData(computeData(grad, normal));
    }
}

void Front::updateConfidence(ImgPixel& Img, int n){
    int w = Img.width(), h = Img.height();

    for (list<Pixel>::iterator i = pixels.begin(); i != pixels.end(); ++i)
    {
        int x = (*i).getX();
        int y = (*i).getY();
        double c = 0;
        for (int i=0;i<2*n+1;i++){
            for (int j=0;j<2*n+1;j++){
                if (0<=x-n+i<=w && 0<=y-n+j<=h){
                    if (Img(x-n+i,y-n+j).getFilled()){
                        c += Img(x-n+i,y-n+j).getConfidence();
                    }
                }
            }
        }

        c = double(c/((2*n+1)*(2*n+1)));
        Img(x,y).setConfidence(c);
    }
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

void update_list(const ImgPixel& Img, std::list<Pixel>& l, int x1, int y1, int x2, int y2)
{
    // Ajouter les points entre (x1,y1) et (x2,y1), entre (x2,y1) et (x2,y2), 
    // entre (x2,y2) et (x1,y2) et entre (x1,y2) et (x1,y1).

    // Ajoute les bords
    for (int i = std::min(x1,x2); i <= std::max(x1,x2); i++) // y1 et y2
    {
        l.push_front(Img(i,y1));
        l.push_front(Img(i,y2));
    }
    for (int j = std::min(y1,y2)+1; j < std::max(y1,y2); j++) // x1 et x2
    // ici on ne met pas les coins afin qu'ils ne soient pas en double
    {
        l.push_front(Img(x1,j));
        l.push_front(Img(x2,j));
    }
}

void update_list(const ImgPixel& Img, std::list<Pixel>& l, Pixel p1, Pixel p2)
{
    int x1 = p1.getX(), y1 = p1.getY();
    int x2 = p2.getX(), y2 = p2.getY();

    update_list(Img,l,x1,y1,x2,y2);
}

