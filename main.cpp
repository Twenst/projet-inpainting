#include "utils.h"
#include "Front.h"
#include "Inpainter.h"
#include "Pixel.h"
#include "Patch.h"

int main()
{
    int zoom=1;
    ImgPixel Img;
    getImage(Img,srcPath("pictures/dog.png"),argc,argv);
    openWindow(Img.width()*zoom, Img.height()*zoom);;
    display(Img,zoom);

    return 0;
}

void algo(ImgPixel Img)
{
    Front front;

    int x1, x2, y1, y2;
    while(selectZone(x1,y1,x2,y2))
    {
        front.defineFront(Img,Pixel(x1,y1), Pixel(x2,y2));
    }
}