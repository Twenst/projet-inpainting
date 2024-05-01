#include "Pixel.h"
#include <cmath>
using namespace std;

Pixel::Pixel(){
}

Pixel::Pixel(int x0,int y0){
    x=x0;
    y=y0;
    filled=false;
}

int Pixel::getX() const{
    return x;
}
int Pixel::getY() const{
    return y;
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
    x=x0;
}

void Pixel::setY(int y0){
    y=y0;
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

void Pixel::initPixel(Color col1, double c1, double d1, bool b1){
    col=col1;
    c=c1;
    d=d1;
    filled=b1;
}


bool Pixel::operator==(Pixel p){
    return( col == p.getColor() and c== p.getConfidence() and d == p.getData() and filled == getFilled());
}

const Pixel& Pixel::operator=(const Pixel& p){
    x=p.x, y=p.y, col=p.col, c=p.c, d=p.d, filled=p.filled;
    return p;
}

double norme(Pixel p){
    int x=p.getX();
    int y=p.getY();
    return(sqrt(x*x + y*y));
}
