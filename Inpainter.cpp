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

void Inpainter::find_front(){
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
            //Img source_patch=

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
