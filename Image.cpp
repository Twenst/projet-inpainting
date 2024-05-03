#include "Image.h"
#include <cmath>
using namespace std;

void display(ImgPixel Img, int coeff){
    int w=Img.width(), h=Img.height();
    Imagine::Image<Color> Img0(w,h);
    for (int i=0;i<w;i++){
        for(int j=0; j<h; j++){
            Img0(i,j)=Img(i,j).getColor();
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
