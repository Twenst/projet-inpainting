#include "Patch.h"
#include <queue>
#include <iostream>
using namespace std;


Patch::Patch(){
}


Patch::Patch(Loc c,int s){
    crds_center=c;
    size=s;
}


Patch::Patch(const Patch & ptch)
{
    crds_center = ptch.crds_center;
    size = ptch.size;
}


Loc Patch::getLocCenter() const{
    return crds_center;
}


int Patch::getSize() const{
    return size;
}


void Patch::setLocCenter(Loc crds){
    crds_center=crds;
}


void Patch::setSize(int s){
    size=s;
}


// Calcul la similarité (=distance euclidienne) entre le patch (sur la frontière) psi_p et la patch psi_q
double distPatch(const Loc& crds_q, const Patch& psi_p, const ImgPixel& I){
    int h = I.height(), w = I.width();
    int n = psi_p.getSize();
    Loc crds_p = psi_p.getLocCenter();
    int x_p = crds_p.getX(), y_p = crds_p.getY();
    int x_q = crds_q.getX(), y_q = crds_q.getY();
    double dist=0;

    for (int k=-n;k<=n;k++){
        for (int l=-n;l<=n;l++){

            if((0<=x_p+k && x_p+k<=w-1 && 0<=y_p+l && y_p+l<=h-1) && I(x_p+k,y_p+l).getFilled()){
                dist+=sqrt(pow((int(I(x_q+k,y_q+l).getColor().r())-int(I(x_p+k,y_p+l).getColor().r())),2)
                             +pow((int(I(x_q+k,y_q+l).getColor().g())-int(I(x_p+k,y_p+l).getColor().g())),2)
                             +pow((int(I(x_q+k,y_q+l).getColor().b())-int(I(x_p+k,y_p+l).getColor().b())),2));
            }
        }
    }

    return dist;
}


// Modifie psi_q tel qu'il soit le patch le plus similaire à psi_p
double argMinDistPatch(Patch& psi_q, const Patch& psi_p, const ImgPixel& I){
    assert(psi_q.getSize() == psi_p.getSize());
    int h = I.height(), w = I.width();
    int n = psi_q.getSize();
    bool filled;

    // On met dans une file les patchs candidats (dans la pratique on ne met que les coordonnées des centres des patchs)
    // Les patchs candidats étant ceux qui sont entièrement remplis
    std::queue<Loc> ListCrdsQX;
    for (int i=n;i<w-n-1;i++){
        for (int j=n; j<h-n-1;j++){
            filled = true;

            for (int k=-n;k<=n;k++){
                for (int l=-n;l<=n;l++){
                    if((0<=i+k && i+k<=w-1 && 0<=j+l && j+l<=h-1) && !I(i+k,j+l).getFilled()){
                        filled = false;
                        break;
                    }
                }
                if (not filled)
                    break;
            }

            if (filled){
                ListCrdsQX.push(I(i,j).getLoc());
            }

        }
    }
    

    // On calcule maintenant la similarité (=distance euclidienne) entre le patch psi_p (sur la frontière) et les patchs candidats
    // et on garde celui qui a la plus petite distance
    assert(not ListCrdsQX.empty());
    double dist;
    Loc crds_q;

    double minDist = distPatch(ListCrdsQX.front(),psi_p,I);
    Loc crds_Q_min = ListCrdsQX.front();
    ListCrdsQX.pop();
    int initSize = ListCrdsQX.size();
    for(int m=0;m<initSize;m++){
        crds_q = ListCrdsQX.front();
        ListCrdsQX.pop();
        dist = distPatch(crds_q,psi_p,I);

        if (dist<=minDist){
            crds_Q_min = crds_q;
            minDist = dist;
            //if(dist==0){                            // On arrête la recherche si la distance est 0 (on ne trouvera théoriquement pas mieux)
            //    psi_q.setLocCenter(crds_Q_min);     // On modifie donc psi_q en conséquence
            //    return 0;
            //}
        }
    }

    psi_q.setLocCenter(crds_Q_min);
    return minDist;
}
