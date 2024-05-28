#pragma once
#include "Image.h"
#include "Pixel.h"
#include "Patch.h"
#include "utils.h"

/* La classe Front permet de définir les méthodes concernant la frontière.
 * La frontière est définie comme une listes de coordonnées de pixel (les coordonnées sont de type Loc)
 *
 * Rq : Les pixels de la frontiere sont REMPLIS ie. getFilled est vrai, sinon c'est l'intérieur de la frontiere
 */

class Front 
{
    std::list<Loc> coords;
public:
    Front();
    Front(std::list<Loc> crds);
    void defineFront(ImgPixel& Img, Loc crds_p1, Loc crds_p2);              // Permet d'initaliser la frontière à partir de (plusieurs) rectangles définis par les points crds_p1 et crds_p2
    void updateFront(const ImgPixel& Img, Patch p);                         // Met à jour la frontière apres avoir appliqué le patch p
    void clearSides(ImgPixel &Img);                                         // Retire la bordure de l'image de la frontière
    Loc coordsMaxPriority(const ImgPixel &Img) ;                            // Parcourt la frontière pour connaître les coordonnées du pixel de priorité maximale
    void updateData(ImgPixel& Img);                                         // Met à jour le terme Data des pixels de la frontière
    void updateConfidence(ImgPixel& Img, int n);                            // Met à jour le terme Confidence des pixels de la frontière
    bool isEmpty();                                                         // Teste si la frontière est vide
    void display();                                                         // Affiche la frontière en noir
};

bool has_unfilled_neighbor(const ImgPixel& Img, Loc crds_p);                // Teste si le pixel de coordonnées crds_p a au moins un voisin qui n'est pas rempli
bool is_within_square(Loc crds_p, Loc crds_c1, Loc crds_c2);                // Teste si p est dans le rectangle défini par c1 et c2
void update_list(const ImgPixel& Img, std::list<Loc>& l, Loc crds_p1, Loc crds_p2);                  // Ajoute le bord du rectangle défini par crds_p1 et crds_p2 à la liste l
