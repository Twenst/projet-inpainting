#include "utils.h"
#include "Front.h"
#include "Inpainter.h"
#include "Pixel.h"
#include "Patch.h"

#include <iostream>
using namespace std;

void algo(Inpainter Inpt);

int main(int argc, char* argv[])
{
    int zoom=1;
    ImgPixel Img;
    getImage(Img,srcPath("pictures/bahamas.png"),argc,argv);
    openWindow(Img.width()*zoom, Img.height()*zoom);;
    display(Img,zoom);

    std::list<Pixel> pixels;
    Front fr(pixels);
    Inpainter Inpt(Img,fr);
    algo(Inpt);

    return 0;
}

void algo(Inpainter Inpt)
{
    // Initialisation de la frontiere
    int x1, x2, y1, y2;

    bool notSelected = selectZone(x1, y1, x2, y2);
    while(notSelected)
    {
        Pixel p1 = Pixel(x1,y1), p2 = Pixel(x2, y2);
        //eraseZone(Inpt.image, p1, p2);
        Inpt.frontier.defineFront(Inpt.image, p1, p2);
        //display(Inpt.image,1);
        Inpt.frontier.clearSides(Inpt.image);
        notSelected = selectZone(x1, y1, x2, y2);
    }


    int n = Inpt.patch_size;
    Inpt.frontier.updateData(Inpt.image);
    Inpt.frontier.updateConfidence(Inpt.image, n);
    Inpt.frontier.display();
    // Boucle principale
    while(not Inpt.frontier.isEmpty())
    {

        // Trouver le pixel de la frontière de priorité maximale
        Pixel p_max = Inpt.frontier.pixelMaxPriority(Inpt.image);
        Patch psi_p(p_max, n);

        drawCircle(p_max.getX(),p_max.getY(),3,PURPLE);

        //cout << "p_max_x = " << p_max.getX() << " ||   ";

        // Trouver le patch \psi_q tq il est le patch le plus proche de \psi_p
        Patch psi_q(Inpt.image(0,0),n);
        double dist = argMinDistPatch(psi_q,psi_p,Inpt.image);
        drawRect(psi_q.getCenter().getX()-n,psi_q.getCenter().getY()-n,2*n+1,n*2+1,RED);
        //anyClick();

        cout << "DISTANCE_q = " << dist << " ||   ";
        //break;

        // Placer le patch \psi_q en p
        Inpt.place_patch(psi_q, p_max);

        //cout << "done11";
        //break;

        // M-a-j les données
        Inpt.frontier.updateData(Inpt.image);
        Inpt.frontier.updateConfidence(Inpt.image, Inpt.patch_size);

        // Affiche l'image
        display(Inpt.image,1);
        Inpt.frontier.display();
    }
}
