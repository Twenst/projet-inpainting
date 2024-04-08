#pragma once
#include "utils.h"

typedef Image<Color,2> Img;
typedef Coords<2> Crds; // il fallait préciser la dimension des coords

class Inpainter{
    Img image;
    Img mask;
    int patch_size;
    Img working_image;
    Img working_mask;
    Img front; //stockage frontière
    Img confidence; //à changer de type, passer sur un tableau ? sauf si changement de type d'image
    Img data;
    Img priority;
public:
    Inpainter(Img im, Img msk, int patch_size = 9); //commentaires
    Img inpaint(); //démarre processus
    bool validate_inputs(); //cheque taille des éléments
    void plot_image(); //gère affichage
    void initialize_attributes(); //initialiser attribus,( confiance...)
    void find_front(); //recherche de la frontière à partir du masque
    void update_priority(); //calcul des priorités
    void update_confidence(); // mise à jour valeurs confiance
    void update_data(); //terme données
    Img calc_normal_matrix(); // calcul de la normale ?
    Img calc_gradient_matrix(); // calcul du gradient
    Crds find_highest_priority_pixel(); //cherche pixel plus grande prioeiré
    Img find_source_patch(Crds target_pixel); //cherche patch idéal
    void update_image(Crds target_pixel, Img source_patch); //copie coller du patch
    Img get_patch(Crds point); //récupère l'image à partir du patch
    double calc_patch_difference(Img im, Img target_patch, Img source_patch);
    bool finished();
};

double patch_area(Img patch);
double patch_shape(Img patch);
double patch_data(Img patch, Img source);
void copy_to_patch(Img dest, Img dest_patch, double data);
