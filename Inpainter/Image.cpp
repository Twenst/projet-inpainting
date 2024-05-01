#include "Image.h"
#include <cmath>
using namespace std;

void affiche(Imagine::Image<pixel> I, int coeff){
    int w=I.width(), h=I.height();
    Imagine::Image<Color> I0(w,h);
    for (int i=0;i<w;i++){
        for(int j=0; j<h; j++){
            I0(i,j)=I(i,j).getColor();
        }
    }

    Imagine::display(I0,0,0,false,coeff);
}

bool getImage(Imagine::Image<pixel> &I,std::string imageLink, int argc, char* argv[]){    // Transverse l'image de lien imageLink (.png) dans l'image I
    Imagine::Image<AlphaColor> I0;  // Image tampon pour récupérer le PNG
    if(! load(I0, argc>1? argv[1]: imageLink)) {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 0;
    }
    int w=I0.width(), h=I0.height();
    I.setSize(w,h);                 // On modifie la taille de I de façon à coller à l'image chargée
    for (int i=0;i<w;i++){
        for (int j=0;j<h;j++){      // Mise en place des paramètres de chaque pixel
            I(i,j).setX(i);
            I(i,j).setY(j);
            I(i,j).setConfidence(1);
            I(i,j).setData(0);
            I(i,j).setColor(I0(i,j));
            I(i,j).setV(true);
        }
    }
    return true;
}
