#include "Inpainter.h"

Inpainter::Inpainter(Image im, Image msk, int patch_size = 9){
}

Image Inpainter::inpaint(){
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

Image Inpainter::calc_normal_matrix(){
}

Image Inpainter::calc_gradient_matrix(){
}

Coords Inpainter::find_highest_priority_pixel(){
}

Image Inpainter::find_source_patch(Coords target_pixel){
}

void Inpainter::update_image(Coords target_pixel, Image source_patch){
}

Image Inpainter::get_patch(Coords point){
}

double Inpainter::calc_patch_difference(Image im, Image target_patch, Image source_patch){
}

bool Inpainter::finished(){
}


double patch_area(Image patch){
}

double patch_shape(Image patch){
}

double patch_data(Image patch, Image source){
}

void copy_to_patch(Image dest, Image dest_patch, double data){
}
