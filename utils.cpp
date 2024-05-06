#include "utils.h"

int min(int a, int b)
{
    return (a>b) ? b : a;
}

int max(int a, int b)
{
    return (a>b) ? a : b;
}

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
    int w=Img.width(), h=Img.height();
    assert(w==Ib.width() && h==Ib.height());
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            Ib(i,j)=byte((int(Img(i,j).getColor().r()) + int(Img(i,j).getColor().g()) + int(Img(i,j).getColor().b()))/3);
        }
    }
}

Image<Color> ImgPixelToImgColor(ImgPixel Img)
{
    int w=Img.width(), h=Img.height();
    Image<Color> I = Image<Color>(w,h);

    for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            I(i,j) = Img(i,j).getColor();
        }
    }

    return I;
}

void computeGradientNormalUsingByte(double gradient[2], double normal[2], ImgPixel Img, Pixel p, ImgByte ImgB)
{
    int w = Img.width(), h = Img.height();
    int x = p.getX(), y = p.getY();

    FVector<byte,2> nrml = Imagine::normal(ImgB,Coords<2>(p.getX(),p.getY()));
    FVector<byte,2> grdt = Imagine::gradient(ImgB,Coords<2>(p.getX(),p.getY()));

    normal[0] = nrml.x();
    normal[1] = nrml.y();
    gradient[0] = grdt.x();
    gradient[1] = grdt.y();
}

/* void computeGradientNormalUsingColor(double gradient[2], double normal[2], ImgPixel Img, Pixel p, ImgByte ImgB)
{
    int w = Img.width(), h = Img.height();
    int x = p.getX(), y = p.getY();

    Image<Color> I = ImgPixelToImgColor(Img);

    FVector<Color,2> nrml = Imagine::normal(I,Coords<2>(p.getX(),p.getY()));
    FVector<Color,2> grdt = Imagine::gradient(I,Coords<2>(p.getX(),p.getY()));

    normal[0] = (nrml.x().r() + nrml.x().g() + nrml.x().b())/3.;
    normal[1] = (nrml.y().r() + nrml.y().g() + nrml.y().b())/3.;
    gradient[0] = (grdt.x().r() + grdt.x().g() + grdt.x().b())/3.;
    gradient[1] = (grdt.y().r() + grdt.y().g() + grdt.y().b())/3.;
} */

void computeGradientNormal(double gradient[2], double normal[2], ImgPixel Img, Pixel p, ImgByte ImgB)
{
    int w = Img.width(), h = Img.height();
    int x = p.getX(), y = p.getY();
    normal[0]=0;
    normal[1]=0;
    gradient[0]=0;
    gradient[1]=0;
    if (x==0 || x==w-1){
    }

    else if (Img(x+1,y).getFilled()){
        if (Img(x-1,y).getFilled()){
            gradient[0]=double(ImgB(x+1,y)-ImgB(x-1,y))/2;
            if (Img(x,y+1).getFilled()){
                normal[0]=0;
                normal[1]=1;
            }
            else {
                normal[0]=0;
                normal[1]=-1;
            }
        }
        else {
            gradient[0]=double(ImgB(x+1,y)-ImgB(x,y))/2;
        }
    }

    else if (Img(x-1,y).getFilled()){
        gradient[0]=double(ImgB(x,y)-ImgB(x-1,y))/2;
    }

    if ( y==0 || y==h-1){
    }

    else if (Img(x,y+1).getFilled()){
        if (Img(x,y-1).getFilled()){
            gradient[0]=double(ImgB(x,y+1)-ImgB(x,y-1))/2;
            if (Img(x+1,y).getFilled()){
                normal[0]=1;
                normal[1]=0;
            }
            else {
                normal[0]=0;
                normal[1]=-1;
            }
        }
        else {
            gradient[0]=double(ImgB(x,y+1)-ImgB(x,y))/2;
        }
    }

    else if (Img(x,y-1).getFilled()){
        gradient[0]=double(ImgB(x,y-1)-ImgB(x,y))/2;
    }
}

double computeData(double gradient[2],double normal[2]) // cd code
{
    double d = gradient[0]*normal[0];
    d += gradient[1]*normal[1];

    return double(absf(d)/alpha);
}
