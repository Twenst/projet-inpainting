#include "Inpainter.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <exception>

// dans le mask: noir = c'est le mask, blanc = c'est pas le mask 

// pour accéder aux éléments de type Image<T,d>, il faut utiliser .data(),
// il faudra tester si l'on accède à ces éléments en faisant 
// comme si c'était une matrice ou comme si c'était un tableau 

Inpainter::Inpainter(Img im, Img msk, int patchsize)
{
    image = im;
    mask = msk;
    patch_size = patchsize;

    // Paramètres non initialisés
    int w = image.width();
    int h = image.height();
    working_image = Img(w,h);
    working_mask = Img(w,h);
    front = Img(w,h);
    confidence = Img(w,h);
    data = Img(w,h);
    priority = Img(w,h);
}

Img Inpainter::inpaint()
{
    // Applique le procédé d'inpainting à l'image
    validate_inputs();
    initialize_attributes();

    bool keep_going = true;
    while (keep_going)
    {
        find_front();
        update_priority();

        Crds target_pixel = find_highest_priority_pixel();
        Img source_patch = find_source_patch(target_pixel);

        update_image(target_pixel, source_patch);

        keep_going = finished();
    }
    
    return working_image;
}

bool Inpainter::validate_inputs()
{
    int w_img = image.width(), h_img = image.height();
    int w_msk = mask.width(), h_msk = mask.height();

    if (w_img != w_msk or h_img != h_msk)
    {
        throw std::invalid_argument("Pas les mêmes tailles d'Image et de Mask!"); // /!\ AJOUTER UN TRY QUI CATCH L'EXCEPTION DANS LE MAIN
    }
}

void Inpainter::plot_image()
{
    //TODO
}

void Inpainter::initialize_attributes()
{
    int w_img = image.width(), h_img = image.height();

    
    for (int i = 0; i < w_img; i++)
    {
        for (int j = 0; j <h_img; j++)
        {
            // Initialisation de confidence
            confidence.data()[i][j] = 1 - mask.data()[i][j];

            // Initialisation de data
            data.data()[i][j] = 0;

            // Initialisation de working_image
            working_image.data()[i][j] = image.data()[i][j];

            // Initialisation de working_mask
            working_mask.data()[i][j] = mask.data()[i][j];
        }
    }
}

bool is_within_bounds(Crds c, int w, int h)
{
    return (0 <= c.x() < w)&&(0 <= c.y() < h);
}

void Inpainter::find_front()
{
    int w = image.width();
    int h = image.height();
    assert(w == front.width() and h == front.height());

    Crds g(-1,0); Crds d(1,0); Crds h(-1,0); Crds b(1,0);
    Crds vois[4] = {g,d,h,b};

    // on réinitialise la frontière d'avant
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            front.data()[i][j] = BLACK;
        }
    }

    // on m-a-j la frontière
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            Crds current(i,j);
            bool has_mask_neighbor = false;
            bool has_non_mask_neighbor = false;
            for (int k = 0; k < 4; k++)
            {
                Crds v = current + vois[k];
                if (is_within_bounds(v,w,h))
                {
                    if (mask.data()[v.x()][v.y()] != BLACK)
                        has_mask_neighbor = true;
                    if (mask.data()[v.x()][v.y()] != WHITE)
                        has_non_mask_neighbor = true;
                }
            }

            if (has_mask_neighbor && has_non_mask_neighbor)
                front.data()[i][j] = WHITE;
        }
    }
}

void Inpainter::update_priority(){
}

void Inpainter::update_confidence(){
}

void Inpainter::update_data(){
}

Img Inpainter::calc_normal_matrix(){
}

Img Inpainter::calc_gradient_matrix(){
}

Crds Inpainter::find_highest_priority_pixel(){
}

Img Inpainter::find_source_patch(Crds target_pixel){
    Img target_patch=get_patch(target_pixel);
    const int width=image.width();
    const int height=image.height();
    Img best_match;
    double best_match_diff = std::numeric_limits<double>::infinity();

    for (int i=0;i<= height - patch_size;i++){
        for (int j=4;j<width - patch_size; j++){
            Img source_patch=working_image.getSubImage(i,j, patch_size,patch_size);


        }
    }

}

void Inpainter::update_image(Crds target_pixel, Img source_patch){
}

Img Inpainter::get_patch(Crds point){
}

double Inpainter::calc_patch_difference(Img im, Img target_patch, Img source_patch){
}

bool Inpainter::finished(){
}


double patch_area(Img patch){
}

double patch_shape(Img patch){
}

double patch_data(Img patch, Img source){
}

void copy_to_patch(Img dest, Img dest_patch, double data){
}
