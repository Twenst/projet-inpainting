#pragma once
#include "utils.h"

class Inpainter{
    Image image;
    Image mask;
    int patch_size;
    Image working_image;
    Image working_mask;
    Image front;
    Image confidence;
    Image data;
    Image priority;
public:
    Inpainter(Image im, Image msk, int patch_size = 9);
    Image inpaint();
    bool validate_inputs();
    void plot_image();
    void initialize_attributes();
    void find_front();
    void update_priority();
    void update_confidence();
    void update_data();
    Image calc_normal_matrix();
    Image calc_gradient_matrix();
    Coords find_highest_priority_pixel();
    Image find_source_patch(Coords target_pixel);
    void update_image(Coords target_pixel, Image source_patch);
    Image get_patch(Coords point);
    double calc_patch_difference(Image im, Image target_patch, Image source_patch);
    bool finished();
};

double patch_area(Image patch);
double patch_shape(Image patch);
double patch_data(Image patch, Image source);
void copy_to_patch(Image dest, Image dest_patch, double data);
