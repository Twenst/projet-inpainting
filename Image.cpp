#include "Image.h"
#include <algorithm>
using namespace std;


// Affiche l'image (les pixels non connus sont affichés en blanc)
void display(ImgPixel Img, int coeff){
    int w=Img.width(), h=Img.height();
    Imagine::Image<Color> Img0(w,h);
    for (int i=0;i<w;i++){
        for(int j=0; j<h; j++){
            if (Img(i,j).getFilled())
                Img0(i,j)=Img(i,j).getColor();
            else Img0(i,j) = WHITE;
        }
    }

    Imagine::display(Img0,0,0,false,coeff);
}


// Transpose les informations de l'image obtenue à partir d'un fichier dans l'image de type ImgPixel
bool getImage(ImgPixel& Img,std::string imageLink, int argc, char* argv[]){
    Imagine::Image<AlphaColor> Img0;
    if(! load(Img0, argc>1? argv[1]: imageLink)) {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 0;
    }

    int w=Img0.width(), h=Img0.height();
    Img.setSize(w,h);
    for (int i=0;i<w;i++){
        for (int j=0;j<h;j++){
            Img(i,j).setX(i);
            Img(i,j).setY(j);
            Img(i,j).setConfidence(1);
            Img(i,j).setData(0);
            Img(i,j).setColor(Img0(i,j));
            Img(i,j).setFilled(true);
        }
    }

    return true;
}


// Supprime (met les pixels en couleur BLANC et en "non remplis") sur la zone délimitée par crds1 et crds2
void eraseZone(ImgPixel& Img, Loc crds1, Loc crds2)
{
    int x1 = crds1.getX(), x2 = crds2.getX();
    int y1 = crds1.getY(), y2 = crds2.getY();

    noRefreshBegin();
    for (int i=std::min(x1,x2)+1;i<std::max(x1,x2);i++){
        for (int j=std::min(y1,y2)+1;j<std::max(y1,y2);j++){
            drawPoint(i,j,WHITE);
            Img(i,j).setColor(WHITE);
            Img(i,j).setFilled(false);
            Img(i,j).setConfidence(0);
        }
    }
    noRefreshEnd();
}
