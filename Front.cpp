#include "Front.h"
#include <algorithm>
using namespace std;


// Les pixels de la frontiere sont REMPLIS ie. getFilled est vrai, sinon c'est l'intérieur de la frontiere


// Teste si le pixel de coordonnées crds_p a au moins un voisin qui n'est pas rempli
bool has_unfilled_neighbor(const ImgPixel& Img, Loc crds_p)
{
    int w = Img.width(), h = Img.height();
    int x = crds_p.getX(), y = crds_p.getY();

    if (x < w-1 and not Img(x+1,y).getFilled())
        return true;
    if (y < h-1 and not Img(x,y+1).getFilled())
        return true;
    if (y > 0 and not Img(x,y-1).getFilled())
        return true;
    if (x > 0 and not Img(x-1,y).getFilled())
        return true;

    return false;
}


// Teste si p est dans le rectangle défini par c1 et c2
bool is_within_square(Loc crds_p, Loc crds_c1, Loc crds_c2) // si p est dans le rectangle défini par c1 et c2
{
    int x = crds_p.getX(), y = crds_p.getY();
    return (std::min(crds_c1.getX(),crds_c2.getX())<=x<=std::max(crds_c1.getX(),crds_c2.getX()) and std::min(crds_c1.getY(),crds_c2.getY())<=y<=std::max(crds_c1.getY(),crds_c2.getY()));
}


Front::Front()
{
}


Front::Front(list<Loc> crds)
{
    coords=crds;
}


// Permet d'initaliser la frontière à partir de (plusieurs) rectangles définis par les points crds_p1 et crds_p2
void Front::defineFront(ImgPixel& Img, Loc crds_p1, Loc crds_p2)
{
    list<Loc> l_front;
    update_list(Img,l_front,crds_p1,crds_p2);                               // Ajoute à la liste l_front les coordonnées des pixels formant le rectangle définit par les coordonnées crds_p1 et crds_p2

    // Ajoute à la frontière les coordonnées des pixels de l_front s'ils sont remplis
    for (list<Loc>::iterator i = l_front.begin(); i != l_front.end(); ++i)
        if (Img((*i).getX(),(*i).getY()).getFilled())
            coords.push_back(*i);

    // Supprime (met les pixels en couleur BLANC et en "non remplis") sur la zone délimitée par crds_p1 et crds_p2
    eraseZone(Img, crds_p1, crds_p2);

    // Retire de la frontière les coordonnées des pixels qui ne sont PAS remplis
    for (list<Loc>::iterator it = coords.begin(); it != coords.end();){
        if(!Img((*it).getX(),(*it).getY()).getFilled()){
            it = coords.erase(it);
        }
        else{
            ++it;
        }
    }

}


// Met à jour la frontière apres avoir appliqué le patch p
void Front::updateFront(const ImgPixel& Img, Patch p)
{
    int w = Img.width(), h = Img.height();
    Loc crds_centre = p.getLocCenter(); int n = p.getSize();
    int x = crds_centre.getX(), y = crds_centre.getY();
    Loc crds_p1(x-n,y-n); Loc crds_p2(x+n,y+n);
    list<Loc> l_patch;
    update_list(Img,l_patch,crds_p1,crds_p2);                               // Ajoute à la liste l_patch les coordonnées des pixels formant le rectangle définit par le patch p

    // On enlève toutes les coordonnées des points de la frontière actuelle qui sont strictement dans le patch
    for(list<Loc>::iterator it = coords.begin(); it != coords.end();){
        if(((*it).getX()>x-n) && ((*it).getX()<x+n) && ((*it).getY()>y-n) && ((*it).getY()<y+n)) {
            it = coords.erase(it);
        }
        else{
            ++it;
        }
    }

    // On maj la nouvelle bordure de la frontiere au niveau du patch en regardant si les pixels du bord du patch ont un voisin non rempli
    for (list<Loc>::iterator i = l_patch.begin(); i != l_patch.end(); ++i)
    {
        int x_patch = (*i).getX();
        int y_patch = (*i).getY();
        if ((0<=x_patch && x_patch<=w-1 && 0<=y_patch && y_patch<=h-1) && has_unfilled_neighbor(Img, *i))
        {
            coords.push_back(*i);
        }
    }
}


// Retire la bordure de l'image de la frontière
void Front::clearSides(const ImgPixel& Img) //enleve les pixels de la frontiere qui sont sur le bord de l'image
{
    int w = Img.width(), h = Img.height();

    for (list<Loc>::iterator i = coords.begin(); i != coords.end(); ++i)
    {
        int x = i->getX(), y = i->getY();
        if (x == 0 or y == 0 or x >= w-1 or y >= h-1)
        {
            coords.remove(*i);
        }
    }
}


// Parcourt la frontière pour connaître les coordonnées du pixel de priorité maximale
Loc Front::coordsMaxPriority(const ImgPixel& Img)
{
    Loc crds_p_max = coords.front();
    for (list<Loc>::iterator i = coords.begin(); i != coords.end(); ++i)
    {
        if (Img(crds_p_max.getX(),crds_p_max.getY()).getPriority() < Img((*i).getX(),(*i).getY()).getPriority())
        {
            crds_p_max = *i;
        }
    }
    return crds_p_max;
}


// Met à jour le terme Data des pixels de la frontière
void Front::updateData(ImgPixel& Img)
{
    int w = Img.width(), h = Img.height();
    double grad[2]; double normal[2];
    ImgByte Ibyte(w,h);
    toImageByte(Img,Ibyte);

    for (list<Loc>::iterator i = coords.begin(); i != coords.end(); ++i)
    {
        computeGradientNormal(grad,normal,Img,*i,Ibyte);
        Img(i->getX(),i->getY()).setData(computeData(grad, normal));
    }
}


// Met à jour le terme Confidence des pixels de la frontière
void Front::updateConfidence(ImgPixel& Img, int n){
    int w = Img.width(), h = Img.height();

    for (list<Loc>::iterator i = coords.begin(); i != coords.end(); ++i)    // Pour CHAQUE pixel 'p' de la frontière, ont fait...
    {
        int x = (*i).getX();
        int y = (*i).getY();
        double c = 0;
        for (int i=0;i<2*n+1;i++){
            for (int j=0;j<2*n+1;j++){
                if (0<=x-n+i && x-n+i<=w-1 && 0<=y-n+j && y-n+j<=h-1){
                    assert((0<=x-n+i && x-n+i<=w-1 && 0<=y-n+j && y-n+j<=h-1));
                    if (Img(x-n+i,y-n+j).getFilled()){
                        c += Img(x-n+i,y-n+j).getConfidence();              // ...la somme des valeurs de Confidence des pixels REMPLIS constituant le patch de centre 'p' de taille n...
                    }
                }
            }
        }

        c = double(c/((2*n+1)*(2*n+1)));                                    //... divisée par la surface du patch.
        assert((0<=x && x<=w-1 && 0<=y && y<=h-1));
        Img(x,y).setConfidence(c);                                          // màj du terme de Confidence du pixel 'p'
    }
}


// Teste si la frontière vide
bool Front::isEmpty()
{
    return coords.empty();
}


// Dessine en noir la frontière
void Front::display()
{
    for (list<Loc>::iterator i = coords.begin(); i != coords.end(); ++i)
    {
        drawPoint(i->getX(), i->getY(), GREEN);
    }
}



void update_list(const ImgPixel& Img, std::list<Loc>& l, int x1, int y1, int x2, int y2)
{
    // Ajouter les points entre (x1,y1) et (x2,y1), entre (x2,y1) et (x2,y2), 
    // entre (x2,y2) et (x1,y2) et entre (x1,y2) et (x1,y1).

    int w = Img.width(), h = Img.height();

    // Ajoute les bords
    for (int i = std::min(x1,x2); i <= std::max(x1,x2); i++) // y1 et y2
    {
        if (0<=i && i<=w-1 && 0<=y1 && y1<=h-1){
            l.push_front(Img(i,y1).getLoc());
        }
        if (0<=i && i<=w-1 && 0<=y2 && y2<=h-1){
            l.push_front(Img(i,y2).getLoc());
        }
    }
    for (int j = std::min(y1,y2)+1; j < std::max(y1,y2); j++) // x1 et x2
    // ici on ne met pas les coins afin qu'ils ne soient pas en double
    {
        if (0<=x1 && x1<=w-1 && 0<=j && j<=h-1){
            l.push_front(Img(x1,j).getLoc());
        }
        if (0<=x2 && x2<=w-1 && 0<=j && j<=h-1){
            l.push_front(Img(x2,j).getLoc());
        }
    }
}


// Ajoute le bord du rectangle défini par crds_p1 et crds_p2 à la liste l
void update_list(const ImgPixel& Img, std::list<Loc>& l, Loc crds_p1, Loc crds_p2)
{
    int x1 = crds_p1.getX(), y1 = crds_p1.getY();
    int x2 = crds_p2.getX(), y2 = crds_p2.getY();

    update_list(Img,l,x1,y1,x2,y2);
}

