// Imagine++ project
// Project: Region Filling and Object Removal by Exemplar-Based ImageInpainting
// Student(s): LEBEL Félix, LEDAUPHIN Titouan, GOSPODARU Téodora, MARTINE Joachim


#include "utils.h"
#include "Front.h"
#include "Inpainter.h"
#include "Pixel.h"
#include "Patch.h"
#include <iostream>
using namespace std;


const int zoom = 1;                                                         // A NE PAS MODIFIER. zoom = 1
const int patch_size = 4;                                                   // La taille d'un patch est 9x9


void algo(Inpainter Inpt);


int main(int argc, char* argv[])
{
    ImgPixel Img;
    getImage(Img,srcPath("pictures/dog.png"),argc,argv);
    openWindow(Img.width()*zoom, Img.height()*zoom);;
    display(Img,zoom);

    std::list<Loc> coords;
    Front fr(coords);
    Inpainter Inpt(Img,fr,patch_size);
    algo(Inpt);

    return 0;
}


void algo(Inpainter Inpt)
{
    // Sélection de la zone à retoucher
    int x1, x2, y1, y2;
    bool notSelected = selectZone(x1, y1, x2, y2);                          // La sélection de zone est en forme de (plusieurs) rectangles
    while(notSelected)
    {
        Loc crds_p1 = Loc(x1,y1), crds_p2 = Loc(x2, y2);
        Inpt.frontier.defineFront(Inpt.image, crds_p1, crds_p2);            // Permet d'ajouter les frontières extérieures du polygones formés à partir des rectangles sélectionnés
        Inpt.frontier.clearSides(Inpt.image);                               // Retire les morceaux de frontière trop procges du bord de l'image
        notSelected = selectZone(x1, y1, x2, y2);
    }

    int n = Inpt.patch_size;                                                // Pendant tout l'algorithme, la taille des patchs est unique
    Inpt.frontier.updateData(Inpt.image);                                   // Calcul des termes de Data sur la frontière
    Inpt.frontier.updateConfidence(Inpt.image, n);                          // Calcul des termes de Confidence sur la frontière
    Inpt.frontier.display();                                                // Affichage de la frontière


    // Boucle principale
    while(not Inpt.frontier.isEmpty())
    {

        // 1) Trouver les coordonnées du pixel de la frontière de priorité maximale
        Loc crds_p_max = Inpt.frontier.coordsMaxPriority(Inpt.image);
        Patch psi_p(crds_p_max, n);                                         // \psi_p est le patch de centre p_max
            //drawCircle(crds_p_max.getX(),crds_p_max.getY(),3,PURPLE);
            drawRect(psi_p.getLocCenter().getX()-n,psi_p.getLocCenter().getY()-n,2*n+1,n*2+1,PURPLE);

        // 2) Trouver le patch \psi_q tel qu il est le patch le plus proche de \psi_p
        Patch psi_q(Loc(0,0),n);
        double dist = argMinDistPatch(psi_q,psi_p,Inpt.image);
            //drawRect(psi_q.getLocCenter().getX()-n,psi_q.getLocCenter().getY()-n,2*n+1,n*2+1,RED);
            //anyClick();


        // 3) Copier le patch \psi_q sur les pixels non remplis du patch \psi_p
        //    et affecter aux pixels non remplis du patch \psi_p la valeur de Confidence du pixel p_max
        Inpt.place_patch(psi_q, crds_p_max);


        // 4) Màj de la frontière après avoir copié le patch
        Inpt.frontier.updateFront(Inpt.image, psi_p);


        // 5) Màj des termes de Data et de Confidence sur la nouvelle frontière
        Inpt.frontier.updateData(Inpt.image);
        Inpt.frontier.updateConfidence(Inpt.image, Inpt.patch_size);


        // Affiche l'image et la frontière
        display(Inpt.image,zoom);
        Inpt.frontier.display();
    }
    endGraphics();
}
