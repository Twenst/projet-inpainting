#include "utils.h"
#include <algorithm>
using namespace std;


// Permet de sélectionner un rectangle sur l'image (deux clics gauches)
bool selectZone(int& x1, int& y1, int& x2, int& y2)
{
    return(getMouse(x1, y1)==1 and getMouse(x2,y2)==1);
}


// Transforme l'image en nuance de gris (utile pour calculer le gradient)
void toImageByte(ImgPixel Img, ImgByte Ib)
{
    int w=Img.width(), h=Img.height();
    assert(w==Ib.width() && h==Ib.height());
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            Ib(i,j)=byte((int(Img(i,j).getColor().r())
                             +int(Img(i,j).getColor().g())
                             +int(Img(i,j).getColor().b()))/3);
        }
    }
}


// Calcule le gradient et le vecteur normal au pixel de coordonnées crds_p
void computeGradientNormal(double gradient[2], double normal[2], ImgPixel Img, Loc crds_p, ImgByte ImgB)
{
    int w = Img.width(), h = Img.height();
    int x = crds_p.getX(), y = crds_p.getY();
    normal[0]=0;
    normal[1]=0;
    gradient[0]=0;
    gradient[1]=0;
    if (x==0||x==w-1){
    }

    else if (Img(x+1,y).getFilled()){
        if (Img(x-1,y).getFilled()){
            gradient[0]=double(ImgB(x+1,y)-ImgB(x-1,y))/2;
            if (Img(x,y+1).getFilled()){
                normal[0]=0;
                normal[1]=-1;
            }
            else {
                normal[0]=0;
                normal[1]=1;
            }
        }
        else {
            gradient[0]=double(ImgB(x+1,y)-ImgB(x,y))/2;
        }
    }

    else if (Img(x-1,y).getFilled()){
        gradient[0]=double(ImgB(x,y)-ImgB(x-1,y))/2;
    }

    if (y==0||y==h-1){
    }

    else if (Img(x,y+1).getFilled()){
        if (Img(x,y-1).getFilled()){
            gradient[1]=double(ImgB(x,y+1)-ImgB(x,y-1))/2;
            if (Img(x+1,y).getFilled()){
                normal[0]=-1;
                normal[1]=0;
            }
            else {
                normal[0]=1;
                normal[1]=0;
            }
        }
        else {
            gradient[1]=double(ImgB(x,y+1)-ImgB(x,y))/2;
        }
    }

    else if (Img(x,y-1).getFilled()){
        gradient[1]=double(ImgB(x,y)-ImgB(x,y-1))/2;
    }
}


// Calcule le terme de donnée à partir du gradient et de la normale
double computeData(double gradient[2],double normal[2])
{
    double ortho_gradient[2] = {gradient[1], -gradient[0]};
    double d = ortho_gradient[0]*normal[0];
    d += ortho_gradient[1]*normal[1];
    return double(abs(d)/alpha);
}

