#include "Inpainter.h"
#include <iostream>
#include <cmath>
#include <limits>

Inpainter::Inpainter(Img im, Img msk, int patchsize)
{
    image = im;
    mask = msk;
    patch_size = patchsize;
}

Img Inpainter::inpaint(){
}

bool Inpainter::validate_inputs(){
}

void Inpainter::plot_image(){
}

void Inpainter::initialize_attributes(){
}

bool is_within_bounds(Crds c, int w, int h)
{
    return (0 <= c.x() < w)&&(0 <= c.y() < h);
}

void Inpainter::find_front()
{
    int w = image.width();
    int h = image.height();

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

    for (int i=0;i<= width - patch_size;i++){
        for (int j=4;j<height - patch_size; j++){
            Img mask_patch = working_mask.getSubImage(i,j, patch_size,patch_size);

            bool not_empty = true ;

            // On regarde si le patch comporte des points dont on ne connaît pas la valeur
            for (int a=0; a<=patch_size;a++){
                for (int b=0; b<=patch_size;b++){
                    if (mask_patch.data()[a][b] == WHITE){
                        not_empty = false ;
                        break;
                    }

                }

            }

            if (not_empty){
                Img source_patch=working_image.getSubImage(i,j, patch_size,patch_size);
                double diff = calc_patch_difference(working_image, target_patch, source_patch);
                if (diff < best_match_diff){
                    best_match=source_patch;
                    best_match_diff= diff;
                }
            }
        }
    }
    return best_match;

}

void Inpainter::update_image(Crds target_pixel, Img source_patch){
}

Img Inpainter::get_patch(Crds point){
    int half_patch_size= (patch_size-1)/2;
    const int width=image.width(); //dans le code python il fait sur working image mais en vrai c'est pareil
    const int height=image.height();
    //on veut renvoyer le patch centré en point mais getSubImage prend en argument le pixel en haut à gauche
    assert((point.x() - half_patch_size) > 0 && (point.y() - half_patch_size) > 0 &&
               (point.x() + half_patch_size) < width && (point.y() + half_patch_size) < height);
    int coord_x = point.x() - half_patch_size;
    int coord_y = point.y() - half_patch_size;

    Img patch= working_image.getSubImage(coord_x,coord_y,patch_size,patch_size);
    return patch;
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
