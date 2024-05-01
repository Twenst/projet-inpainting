#pragma once
#include "Image.h"
#include "Pixel.h"
#include "Patch.h"
#include "utils.h"

class Front {
    std::list<Pixel> pixels;
public:
    Front();
    Front(std::list<Pixel> pxs);
    void defineFront(const ImgPixel& Img, std::list<Pixel> list_pixels);    // Définit la frontière à partir d'une liste de pixels (les pixels non-remplis sont exclus de la frontière)
    void updateFront(const ImgPixel& Img, std::list<Pixel> list_pixels);    // Met à jour la frontière à partir d'une liste de pixels (les pixels non-remplis sont exclus de la frontière)
    void clearSides(const ImgPixel& Img);                                   // Retire la bordure de l'image de la frontière
    Pixel pixelMaxPriority();                                               // Parcourt la frontière pour connaître le pixel de priorité maximale
    void updateData(ImgPixel& Img);                                         // Met à jour les termes Data des pixels de la frontière
    bool isEmpty();                                                         // Teste si la frontière est vide
    void display();                                                         // Affiche la frontière en noir
};
