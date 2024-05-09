#pragma once
#include "Pixel.h"
#include "Image.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

/* La classe Patch permet d'agir sur des éléments plus gros que des pixels.
 * Un Patch étant défini comme l'ensemble des pixels situés dans le carré de centre de coordonnées "crds_center" et
 * de côté de taille "size".
 */

class Patch {
    Loc crds_center;
    int size;

public :
    Patch();
    Patch(Loc c, int s);
    Patch(const Patch & ptch);
    Loc getLocCenter() const ;
    int getSize() const ;
    void setLocCenter(Loc crds);
    void setSize(int s);
};

double distPatch(const Loc& crds_q, const Patch& psi_p, const ImgPixel& I);   // Calcul la similarité (=distance euclidienne) entre le patch (sur la frontière) psi_p et la patch psi_q
double argMinDistPatch(Patch& psi_q, const Patch& psi_p, const ImgPixel& I);  // Modifie psi_q tel qu'il soit le patch le plus similaire à psi_p
