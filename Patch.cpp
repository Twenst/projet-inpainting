#include "Patch.h"
#include <queue>


Patch::Patch(){
}

Patch::Patch(Pixel c,int s){
    center=c;
    size=s;
}

/* Patch::Patch(const Patch & ptch)
{
    center = ptch.center;
    size = ptch.size;
} */

Pixel Patch::getCenter() const{
    return center;
}

int Patch::getSize() const{
    return size;
}

void Patch::setCenter(Pixel p){
    center=p;
}

void Patch::setSize(int s){
    size=s;
}

void Patch::updateConfidence(ImgPixel Img){
    int x = center.getX();
    int y = center.getY();
    int n = size;
    double c = 0;
    for (int i=0;i<2*n+1;i++){
        for (int j=0;j<2*n+1;j++){
            if (Img(x-n+i,y-n+j).getFilled()){
                c += Img(x-n+i,y-n+j).getConfidence();
            }
        }
    }

    c = double(c/((2*n+1)*(2*n+1)));

    for (int i=0;i<2*n+1;i++){
        for (int j=0;j<2*n+1;j++){
            if (!Img(x-n+i,y-n+j).getFilled()){
                Img(x-n+i,y-n+j).setConfidence(c);
            }
        }
    }
}

int distPatch(const Pixel& q, const Patch& psi_p, const ImgPixel& I){ //renvoie la distance induite par la norme 2 sur les tampons
    int n = psi_p.getSize();
    Pixel p = psi_p.getCenter();
    int x_p = p.getX(), y_p = p.getY();
    int x_q = q.getX(), y_q = q.getY();
    int dist=0;

    for (int k=-n;k<=n;k++){
        for (int l=-n;l<=n;l++){
            if(I(x_p+k,y_p+l).getFilled()){
                dist+=sqrt( pow((int(I(x_q+k,y_q+l).getColor().r())-int(I(x_p+k,y_p+l).getColor().r())),2)
                             +pow((int(I(x_q+k,y_q+l).getColor().g())-int(I(x_p+k,y_p+l).getColor().g())),2)
                             +pow((int(I(x_q+k,y_q+l).getColor().b())-int(I(x_p+k,y_p+l).getColor().b())),2)
                             );
            }
        }
    }

    return dist;
}

int argMinDistPatch(Patch& psi_q, const Patch& psi_p, const ImgPixel& I){
    assert(psi_q.getSize() == psi_p.getSize());
    int h = I.height(), w = I.width();
    int n = psi_q.getSize();
    bool filled;
    std::queue<Pixel> ListQX;

    for (int i=n;i<w-n-1;i++){
        for (int j=n; j<h-n-1;j++){      // Les sample potentiels sont ceux de coordonné (i,j). Au dela de ces valeurs, Psy_q n'est plus carré
            filled = true;                   // Cherchons les q potentiel (ceux dont Psy_q est "plein")

            for (int k=-n;k<=n;k++){
                for (int l=-n;l<=n;l++){
                    if(not I(i+k,j+l).getFilled()){
                        filled = false;
                        break;           //Sortie des boucles
                    }
                }
                if (not filled)
                    break;
            }
            if (filled){
                ListQX.push(I(i,j));
            }
        }
    }

    //On a désormait la liste des pixels potentiels, il faut calculer leur distance pour trouver le meilleur matching
    assert(not ListQX.empty()); // La liste ne doit pas être vide
    int dist;
    Pixel q;
    int minDist = distPatch(ListQX.front(),psi_p,I);
    Pixel Q_min = ListQX.front();
    ListQX.pop();

    int initSize = ListQX.size();
    for(int m=0;m<initSize;m++){ //Tant que la liste n'est pas vide
        q = ListQX.front();
        ListQX.pop();

        dist = distPatch(q,psi_p,I);

        if (dist<=minDist){
            Q_min = q;
            minDist = dist;
            if(dist==0){    //cas matching optimal
                std::cout<<"Perfect match!"<<std::endl;
                return 0;
            }
        }
    }
    return minDist;
}

void Patch::set_filled(ImgPixel Img)
{
    int w = Img.width(), h = Img.height();
    Pixel x0(0,0); Pixel xf(w-1,h-1);

    for (int i = 0; i < 2*size+1; i++)
    {
        for (int j = 0; j < 2*size+1 ;j++)
        {
            Img(center.getX()-size+i, center.getY()-size+j).setFilled(true);
        }
    }
}
