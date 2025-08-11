#include "../../cub3d.h"


// Pourquoi on a besoin de wall_texture_x ?
// Lorsqu'on projette un rayon sur un mur :

// On détecte quelle texture utiliser (mur nord, sud, est ou ouest).
// Mais pour afficher le mur correctement, il faut savoir quelle colonne de la texture correspond à la colonne de l'écran.

// Exemple :

// L'écran affiche 100 colonnes (screen_x = 0 à 99).
// La texture du mur fait 64 pixels de large.
// Si le rayon frappe un mur à 40 % de sa largeur, il faut prendre la colonne 25 (≈ 64 × 0.4) dans la texture.
// screen_x = colonne à dessiner sur l’écran
// Chaque colonne correspond à un rayon qui part de la caméra.
// On calcule la direction du rayon en fonction de la direction du joueur et de la caméra.


// On trace ce rayon dans la map (DDA) jusqu’à rencontrer un mur '1'.
// Une fois qu’on a trouvé l’impact sur le mur, on sait :
// Si c’est un mur Nord/Sud ou Est/Ouest.
// La coordonnée exacte du point d’impact sur le mur.

// Avec cette coordonnée, on calcule où on est sur la texture :
// wall_x = partie décimale du point d’impact
// wall_hit_x  = wall_x * texture_width
// C’est là qu’intervient wall_hit_x, il indique quelle colonne dans la texture afficher pour ce rayon.

// Exemple :

// Colonne x = 300 (écran).
// Rayon frappe un mur Est à la coordonnée ray_current_tile_x = 4.3.
// La partie fractionnaire (0.3) indique où on est sur ce mur.
// Si la texture fait 64 px de large :

// wall_hit_x = 0.3 * 64 ≈ 19
// Donc on prend la colonne 19 de la texture et on la projette sur la colonne 300 de l’écran.


// Enfin, on dessine la colonne x de l’écran avec la texture correspondante.

// screen_x
// screen_x est l’index de la colonne sur ton écran (en pixels).

// Ex. : Si ton écran fait screen_width = 800, alors screen_x va de 0 à 799.
// Il sert à savoir où dessiner la colonne calculée.

// wall_hit_x
// C’est la position horizontale dans la texture du mur (en pixels aussi, mais dans la texture).
// Elle est calculée à partir de l’endroit exact où ton rayon touche le mur dans le monde.



void render_frame(void *setting)
{
    t_resources                 *resources;
    t_raycast_data              raycast_data;
    t_ray_column_norm_helper    helper;
    int                         screen_x;
    

    resources = (t_resources *)setting;
    if (resources->screen == NULL)
        write_and_exit_with_graphics_error(ERROR_SCREEN_NOT_INITIALIZED, resources);

    screen_x = 0;
    while (screen_x < resources->dimensions_config.screen_width)
    {
        // Initialiser le rayon pour la colonne x
        init_raycast(resources, screen_x, &raycast_data);

        // Calculer l'impact avec le mur via DDA
        raycast_digital_differential_analyzer(resources, &raycast_data);

        // Choisir la texture et coordonnée dans cette texture
        helper.texture = determine_texture_and_hit_column(resources, &raycast_data, &helper.wall_hit_x);

        // Dessiner la colonne sur l'écran
        draw_entire_pixel_column(resources, screen_x, &raycast_data, &helper);
        screen_x = screen_x + 1;
    }
    render_compass(resources);
}



