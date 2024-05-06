#pragma once
#include "Image.h"
#include "Pixel.h"
#include "Patch.h"
#include "utils.h"

class Front 
{
    std::list<Pixel> pixels;
public:
    Front();
    Front(std::list<Pixel> pxs);
    Front(const Front & frt);
    void defineFront(const ImgPixel& Img, Pixel p1, Pixel p2);              // Ajoute le rectange défini par p1 et p2 à la frontière
    void defineFront(const ImgPixel& Img, std::list<Pixel> front_pixels);   // Définit la frontière à partir d'une liste de pixels (les pixels non-remplis sont exclus de la frontière)
    void updateFront(const ImgPixel& Img, Patch p);                         // Met à jour la frontière apres avoir appliqué le patch défini par les points p1 et p2
    void clearSides(const ImgPixel& Img);                                   // Retire la bordure de l'image de la frontière
    Pixel pixelMaxPriority() ;                                              // Parcourt la frontière pour connaître le pixel de priorité maximale
    void updateData(ImgPixel& Img);                                         // Met à jour les termes Data des pixels de la frontière
    bool isEmpty();                                                         // Teste si la frontière est vide
    void display();                                                         // Affiche la frontière en noir
};

bool has_unfilled_neighbor(const ImgPixel& Img, Pixel p);
bool is_within_square(Pixel p, Pixel c1, Pixel c2);                         // si p est dans le rectangle défini par c1 et c2
void update_list(std::list<Pixel>& l, Pixel p1, Pixel p2);                  // ajoute le bord du rectangle à la liste