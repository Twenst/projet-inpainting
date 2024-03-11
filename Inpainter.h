#pragma once
#include "utils.h"

typedef Image<char> Img; // il fallait préciser le taille de notre image, char = [0,255]
typedef Coords<2> Crds; // il fallait préciser la dimension des coords!


class Inpainter{
    Img image;
    Img mask;
    int patch_size;
    Img working_image;
    Img working_mask;
    Img front;
    Img confidence;
    Img data;
    Img priority;
public:
    Inpainter(Img im, Img msk, int patch_size = 9);
    Img inpaint();
    bool validate_inputs();
    void plot_image();
    void initialize_attributes();
    void find_front();
    void update_priority();
    void update_confidence();
    void update_data();
    Img calc_normal_matrix();
    Img calc_gradient_matrix();
    Crds find_highest_priority_pixel();
    Img find_source_patch(Crds target_pixel);
    void update_image(Crds target_pixel, Img source_patch);
    Img get_patch(Crds point);
    double calc_patch_difference(Img im, Img target_patch, Img source_patch);
    bool finished();
};

double patch_area(Img patch);
double patch_shape(Img patch);
double patch_data(Img patch, Img source);
void copy_to_patch(Img dest, Img dest_patch, double data);
