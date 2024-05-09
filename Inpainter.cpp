#include "Inpainter.h"
#include <iostream>
using namespace std;


Inpainter::Inpainter(){
}


Inpainter::Inpainter(ImgPixel Img, Front fr){
    image=Img;
    frontier=fr;
    patch_size = 4; // cela fait un patch effective de 9x9
}


// Copie le patch \psi_q sur les pixels non remplis du patch \psi_p
// et affecte aux pixels non remplis du patch \psi_p la valeur de Confidence du pixel p_max
void Inpainter::place_patch(Patch psi_q, Loc crds_p)
{
    int w = image.width(), h = image.height();
    int x = crds_p.getX();
    int y = crds_p.getY();
    int n = psi_q.getSize();
    int q_size = 2*n+1;

    // Pour chaque pixel du patch psi_p qui est non rempli (et dans l'image), copie les termes de Color et Confidence (et met à jour le fait que
    // le pixel est rempli) à partir du pixel du patch psi_q (patch de plus grande similitude) correspondant
    for (int i = 0; i < q_size; i++)
    {
        for (int j = 0; j < q_size; j++)
        {
            int a = x-n+i, b = y-n+j;
            int c = psi_q.getLocCenter().getX()-n+i, d = psi_q.getLocCenter().getY()-n+j;
            if (0<=a && a<=w && 0<=b && b<=h && 0<=c && c<=w && 0<=d && d<=h)
            {
                if (not image(a,b).getFilled())
                {
                    image(a,b).setColor(image(c,d).getColor());
                    image(a,b).setConfidence(image(x,y).getConfidence());
                    image(a,b).setFilled(image(c,d).getFilled());
                }
            } else {
                cout << "there is an issue! ";
            }
        }
    }

}
