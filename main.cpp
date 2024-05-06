#include "utils.h"
#include "Front.h"
#include "Inpainter.h"
#include "Pixel.h"
#include "Patch.h"

int main(int argc, char* argv[])
{
    int zoom=1;
    ImgPixel Img;
    getImage(Img,srcPath("pictures/dog.png"),argc,argv);
    openWindow(Img.width()*zoom, Img.height()*zoom);;
    display(Img,zoom);

    return 0;
}

void algo(Inpainter Inpt)
{
    // Initialisation de la frontiere
    int x1, x2, y1, y2;
    while(selectZone(x1,y1,x2,y2))
    {
        Inpt.frontier.defineFront(Inpt.image,Pixel(x1,y1), Pixel(x2,y2));
    }
    Inpt.frontier.clearSides(Inpt.image);

    // Boucle principale
    while(not Inpt.frontier.isEmpty())
    {
        // Trouver le pixel de la frontière de priorité maximale
        Pixel p_max = Inpt.frontier.pixelMaxPriority();
        Patch psi_p(p_max, Inpt.patch_size);

        // Trouver le patch \psi_q tq il est le patch le plus proche de \psi_p
        Patch psi_q;
        argMinDistPatch(psi_q,psi_p,Inpt.image);

        // Placer le patch \psi_q en p
        Inpt.place_patch(psi_q, p_max);
        
        // M-a-j les données
        Inpt.frontier.updateData(Inpt.image);
        // OU EST CE QU'ON MAJ LE TERME CONFIDENCE?
    }
}