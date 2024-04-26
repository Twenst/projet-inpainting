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

bool Inpainter::validate_inputs(int x) // x sert juste à faire un overload, dans le code python cette fonction est un void
{
    int w_img = image.width(), h_img = image.height();
    int w_msk = mask.width(), h_msk = mask.height();

    return (w_img != w_msk or h_img != h_msk) ? false : true;
}

void Inpainter::validate_inputs()
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

void Inpainter::update_priority()
{
    update_confidence();
    update_data();

    int w = image.width();
    int h = image.height();

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            priority.data()[i][j] = confidence.data()[i][j] * data.data()[i][j] * front.data()[i][j];
        }
    }
}

void Inpainter::update_confidence()
{
    Img new_conf = confidence.clone();

    int w = image.width();
    int h = image.height();

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (front.data()[i][j] == WHITE)
            {
                Img patch = get_patch(Crds(i,j));
                // new_conf.data()[i][j] = 
                // patch_data(patch, confidence) 
                // IL Y A UN SOUCIS AVEC LES FONCTIONS PATCH_*
            }
        }
    }
}

void Inpainter::update_data()
{

}

Img Inpainter::calc_normal_matrix()
{
    float x_kernel[3][3] = { {0.25, 0., -0.25},
                             {.5, 0., -0.5},
                             {0.25, 0., -0.25}
                           };
    float y_kernel[3][3] = { {-0.25, -0.5, -0.25},
                             {0., 0., 0.},
                             {0.25, 0.5, 0.25}
                           };
}

Img Inpainter::calc_gradient_matrix(){
}

Crds Inpainter::find_highest_priority_pixel(){
}

Img Inpainter::find_source_patch(Crds target_pixel)
{
    Img target_patch=get_patch(target_pixel);
    const int width=image.width();
    const int height=image.height();
    Img best_match;
    double best_match_diff = std::numeric_limits<double>::infinity();

    for (int i=0;i<= width - patch_size;i++){
        for (int j=0;j<height - patch_size; j++){
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

            //s'il n'en contient pas on regarde sa différence par rapport au patch que l'on veut remplir et on remplace best_match si nécessaire
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
    //on récupère le coin en haut à gauche du patch que l'on veut remplir
    int half_patch_size= (patch_size-1)/2;
    const int width=image.width(); //dans le code python il fait sur working image mais en vrai c'est pareil
    const int height=image.height();
    //on veut renvoyer le patch centré en point mais getSubImage prend en argument le pixel en haut à gauche
    assert((target_pixel.x() - half_patch_size) > 0 && (target_pixel.y() - half_patch_size) > 0 &&
           (target_pixel.x() + half_patch_size) < width && (target_pixel.y() + half_patch_size) < height);
    int coord_x = target_pixel.x() - half_patch_size;
    int coord_y = target_pixel.y() - half_patch_size;
    int confidence_target_pixel = confidence.data()[coord_x][coord_y]; //valeur de confiance du pixel autour duquel on remplace


    //on ne va modifier que les pixels qui sont blancs sur working_mask
    //dans le code python il modifie aussi le pixel en haut à gauche mais ça me semble inutile donc je l'ai pas fait
    for (int a=0; a<=patch_size;a++){
        for (int b=0; b<=patch_size;b++){
            if (working_mask.data()[coord_x+a][coord_y+b] == WHITE){
                working_mask.data()[coord_x+a][coord_y+b] = BLACK; //on modifie leur couleur sur working_mask car ils sont remplis
                working_image.data()[coord_x+a][coord_y+b] = source_patch.data()[a][b]; //on met la vraie couleur sur working_image
                confidence.data()[coord_x+a][coord_y+b] = confidence_target_pixel; //on met la bonne valeur de confiance

            }

        }

    }
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
    //contrairement à la fonction du code python on ne peut pas avoir de patch centré en un point trop proche du bord à voir si ça pose pb
    //dans python la 1ère coordonnée correspond à la hauteur du pixel alors qu'ici x est l'axe de la largeur
    //dans le code python dans get_patch patch[0] contient [y_min,y_max] et patch[1] contient [x_min,x_max] alors qu'ici on a une image
}

double Inpainter::calc_patch_difference(Img im, Img target_patch, Img source_patch){
}

bool Inpainter::finished(){
}


double patch_area(Img patch){
}

Crds patch_shape(Img patch)
{
    return Crds(patch.width(),patch.height());
}

double patch_data(Img patch, Img source)
{

}

void copy_to_patch(Img dest, Img dest_patch, double data){
}
