#include "Inpainter.h"

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
    int q_size = 2*psi_q.getSize()+1;

    for (int i = 0; i < q_size; i++)
    {
        for (int j = 0; j < q_size; j++)
        {
            int a = x-psi_q.getSize()+i, b = y-psi_q.getSize()+j;
            int c = psi_q.getCenter().getX()-psi_q.getSize()+i, d = psi_q.getCenter().getY()-psi_q.getSize()+j;
            if (is_within_square(Pixel(a,b), Pixel(0,0), Pixel(w,h)) and
            is_within_square(Pixel(a,b), Pixel(0,0), Pixel(w,h)) and
            not image(a,b).getFilled())
            {
                image(a,b) = image(c,d);
            }
        }
    }

    // m-a-j de la frontiere, mets en rempli les points du patch
    frontier.updateFront(image, Patch(p,psi_q.getSize())); 
}