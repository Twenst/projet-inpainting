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

void Inpainter::place_patch(Patch psi_q, Pixel p)
{
    // m-a-j de l'image
    int w = image.width(), h = image.height();
    int x = p.getX();
    int y = p.getY();
    int n = psi_q.getSize();
    int q_size = 2*n+1;

    //cout << psi_q.getCenter().getX();

    for (int i = 0; i < q_size; i++)
    {
        for (int j = 0; j < q_size; j++)
        {
            int a = x-n+i, b = y-n+j;
            int c = psi_q.getCenter().getX()-n+i, d = psi_q.getCenter().getY()-n+j;
            if (0<=a && a<=w && 0<=b && b<=h && 0<=c && c<=w && 0<=d && d<=h)
            {
                if (not image(a,b).getFilled())
                {
//                    cout << "okay for now ";
//                    cout << c << " " << w << "   // ";
//                    cout << d << " " << h << "   // ";
                    image(a,b).setColor(image(c,d).getColor());
                    //image(a,b).setData(image(c,d).getData());
                    image(a,b).setConfidence(image(x,y).getConfidence());
                    image(a,b).setFilled(image(c,d).getFilled());
                }
            } else {
                cout << "there is issue! ";
            }
        }
    }

    Patch psi_p(p,n);
    //psi_p.updateConfidence(image);
    //psi_p.set_filled(image);

    // m-a-j de la frontiere, mets en rempli les points du patch
    frontier.updateFront(image, psi_p);
}
