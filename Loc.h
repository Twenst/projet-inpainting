#pragma once

/* La classe Loc définit les coordonnées des pixels de l'Image.
 * Cette classe est très utile lorsqu'on manipule la frontière (liste des coordonnées des pixels constituant la frontière)
 * car elle permet de manipuler des objets simples et non ambigus.
 */

class Loc
{
private:
    int x,y;                                // Position x et y du pixel

public:
    Loc();
    Loc(int x0,int y0);
    int getX() const;
    int getY() const;
    void setX(int x0);
    void setY(int y0);
    void setXY(int x0, int y0);

    bool operator==(Loc crds);
    const Loc& operator=(const Loc& crds);
};

