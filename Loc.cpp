#include "Loc.h"

Loc::Loc(){
}

Loc::Loc(int x0,int y0){
    x = x0;
    y = y0;
}

int Loc::getX() const{
    return x;
}

int Loc::getY() const{
    return y;
}

void Loc::setX(int x0){
    x = x0;
}

void Loc::setY(int y0){
    y = y0;
}

void Loc::setXY(int x0, int y0){
    x = x0;
    y = y0;
}

const Loc& Loc::operator=(const Loc& crds){
    x=crds.getX(), y=crds.getY();
    return crds;
}

bool Loc::operator==(Loc crds){
    return(x == crds.getX() and y == crds.getY());
}
