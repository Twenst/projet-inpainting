#include "Front.h"
#include <cmath>
using namespace std;

Front::Front(){
}

Front::Front(std::list<Pixel> pxs){
    pixels=pxs;
}

void Front::defineFront(const ImgPixel& Img, std::list<Pixel> list_pixels){

}







bool selectZone(int& x1,int& y1,int& x2,int& y2){
    return(getMouse(x1, y1)==1 && getMouse(x2,y2)==1);
    /* demande deux clics gauches, remplit x1, y1, x2 et y2 avec les coordonnées des clics et retourne True
     * En cas de clic droit, retourne False
     */
}
