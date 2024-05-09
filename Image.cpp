#include "Image.h"
#include <algorithm>
using namespace std;

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

bool getImage(ImgPixel& Img,std::string imageLink, int argc, char* argv[]){    // Transverse l'image de lien imageLink (.png) dans l'image I
    Imagine::Image<AlphaColor> Img0;  // Image tampon pour récupérer le PNG
    if(! load(Img0, argc>1? argv[1]: imageLink)) {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 0;
    }
    int w=Img0.width(), h=Img0.height();
    Img.setSize(w,h);                 // On modifie la taille de I de façon à coller à l'image chargée
    for (int i=0;i<w;i++){
        for (int j=0;j<h;j++){      // Mise en place des paramètres de chaque pixel
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

void eraseZone(ImgPixel& Img, Pixel p1, Pixel p2)
{
    int x1 = p1.getX(), x2 = p2.getX();
    int y1 = p1.getY(), y2 = p2.getY();

    noRefreshBegin();                                   //Permettra de gagner du temps de calcul
    for (int i=std::min(x1,x2)+1;i<std::max(x1,x2);i++){
        for (int j=std::min(y1,y2)+1;j<std::max(y1,y2);j++){
            drawPoint(i,j,WHITE);                       //Dessine le pixel en blanc sur l'affichage
            Img(i,j).setColor(WHITE);                    //Remplace la couleur du pixel par blanc
            Img(i,j).setFilled(false);                            //Met le pixel sur "non visité"
            Img(i,j).setConfidence(0);                   //Met la confiance du pixel à 0
        }
    }
    noRefreshEnd();
}
