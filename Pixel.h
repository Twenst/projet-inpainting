#pragma once
#include "Loc.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

const int alpha=255;

/* Les éléments de type Pixel sont les éléments qui constituent l'Image.
 * Ils contiennent les coordonnées des pixels (de type Loc), la couleur du pixel, et les termes de "Confidence" et de "Data".
 * Le booléen "filled" traduit le fait que le pixel soit connu (=rempli) ou non.
 */

class Pixel 
{
private:
    Loc coords;
    Color col;
    double c,d;
    bool filled;

public:
    Pixel();
    Pixel(int x0,int y0);
    int getX() const;
    int getY() const;
    Loc getLoc() const;
    Color getColor() const;
    double getConfidence() const;
    double getData() const;
    double getPriority() const;
    bool getFilled() const;
    void setX(int x0);
    void setY(int y0);
    void setColor(Color color);
    void setConfidence(double conf);
    void setData(double data);
    void setFilled(bool b0);

    bool operator==(Pixel p);
    const Pixel& operator=(const Pixel& p);
};
