#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;

const int alpha=255;

class Pixel 
{
    int x,y;        // position
    Color col;      // Color
    double c,d;     // Confidence and Data term
    bool filled;         // false if not filled yet, true else

public:
    Pixel();
    Pixel(int x0,int y0);
    int getX() const;
    int getY() const;
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
    void initPixel(Color col1, double c1, double d1, bool v1);

    bool operator==(Pixel p);
    const Pixel& operator=(const Pixel& p);
};

double norme(Pixel p);
