#include "Pixel.h"
#include <cmath>
using namespace std;

Pixel::Pixel(){
}

Pixel::Pixel(int x0,int y0){
    coords.setXY(x0,y0);
    filled=false;
}

int Pixel::getX() const{
    return coords.getX();
}

int Pixel::getY() const{
    return coords.getY();
}

Loc Pixel::getLoc() const{
    return coords;
}

Color Pixel::getColor() const{
    return col;
}
double Pixel::getConfidence() const{
    return c;
}
double Pixel::getData() const{
    return d;
}
double Pixel::getPriority() const{
    return c*d;
}
bool Pixel::getFilled() const{
    return filled;
}

void Pixel::setX(int x0){
    coords.setX(x0);
}

void Pixel::setY(int y0){
    coords.setY(y0);
}

void Pixel::setColor(Color color){
    col=color;
}

void Pixel::setConfidence(double conf){
    c=conf;
}

void Pixel::setData(double dat){
    d=dat;
}

void Pixel::setFilled(bool b0){
    filled=b0;
}

bool Pixel::operator==(Pixel p){
    return( col == p.getColor() and c== p.getConfidence() and d == p.getData() and filled == getFilled());
}

const Pixel& Pixel::operator=(const Pixel& p){
    coords=p.coords, col=p.col, c=p.c, d=p.d, filled=p.filled;
    return p;
}
