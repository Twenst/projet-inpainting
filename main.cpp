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
