#include "../../cub3d.h"



// on extrait la couleur d’un pixel d’une image aux coordonnées (x, y)
// MLX stocke les pixels en format RGBA (4 octets par pixel)

// img->width = nombre de pixels par ligne.
// y * img->width = combien de pixels avant d'arriver à la ligne y.
// + x = décalage dans la ligne pour atteindre la colonne x.

// la codam stocke les pixels des images dans un tableau simple, pas en deux dimensions ou plus.
// &img->pixels permet d'obtenir le pixel.

// on veut par exemple la ligne y = 0 et x = 6 :   
// y * img->width + x    
// = 0 x 64 + 6 
// = 6

// puis on fait * 4 car il ya 4 octets (32 bits) par pixel [AAAA AAAA][RRRR RRRR][GGGG GGGG][BBBB BBBB]

uint32_t convert_rgba_to_argb(const mlx_image_t *image, int x, int y)
{
    int             pixel_index;
    const uint8_t   *rgba;
    uint32_t        final_color;

    pixel_index = (y * image->width + x);
    rgba = &image->pixels[pixel_index * 4];
    final_color = ((uint32_t)rgba[0] << 24)   // Alpha
                | ((uint32_t)rgba[1] << 16)   // Rouge
                | ((uint32_t)rgba[2] <<  8)   // Vert
                |  (uint32_t)rgba[3];         // Bleu
    return (final_color);
}




// Réduit la luminosité d'une couleur en divisant chaque composante R, G, B par 2.
// L'alpha (stocké dans le dernier octet) reste inchangé pour conserver l'opacité.

// Format interne attendu :
// [RRRR RRRR][GGGG GGGG][BBBB BBBB][AAAA AAAA]

// Masques utilisés :
// - 0x000000FF = 00000000 00000000 00000000 11111111 (isole Alpha)
// - 0x00FFFFFF = 00000000 11111111 11111111 11111111 (isole RGB après décalage)
// - 0x007F7F7F = 00000000 01111111 01111111 01111111 (limite chaque composante après division)

// rgb = (rgb >> 1) & 0x007F7F7F;
// Après shift sans masque :
// 00000000 0RRRRRRR RGGGGGGG GBBBBBBB    pollution entre canaux
// Après masque :
// 00000000 0RRRRRRR 0GGGGGGG 0BBBBBBB    propre

uint32_t shade_color(uint32_t color)
{
    uint32_t alpha;
    uint32_t rgb;
    uint32_t final_rgb;

    // Étape 1 : Extraire Alpha (dernier octet)
    // Exemple :
    // color  = RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA
    // masque = 00000000 00000000 00000000 11111111
    alpha = color & 0x000000FF;

    // Étape 2 : Extraire les composantes RGB
    // Décalage de 8 bits à droite pour supprimer Alpha
    // Après >> 8    : 00000000 RRRRRRRR GGGGGGGG BBBBBBBB
    // masque        : 00000000 11111111 11111111 11111111
    rgb = (color >> 8) & 0x00FFFFFF;

    // Étape 3 : Diviser chaque composante par 2 (pour simuler l'ombre)
    // >> 1 divise toutes les composantes (R, G, B) par 2
    // masque 0x007F7F7F (01111111 pour chaque octet) empêche
    // la propagation des bits sur l'octet suivant après le décalage
    rgb = (rgb >> 1) & 0x007F7F7F;

    // Étape 4 : Recomposer la couleur finale
    // Décale RGB à gauche pour retrouver sa position
    // Puis ajoute Alpha inchangé
    final_rgb = ((rgb << 8) | alpha);

    return (final_rgb);
}





//  Dessine un pixel dans une image MLX42 à la position (x, y) avec la couleur donnée.
//  
//  Cette fonction ajoute une vérification des bornes pour éviter d'écrire
//  en dehors du buffer d'image, ce qui pourrait provoquer des segfaults.

//   - x doit être compris entre 0 et img->width - 1
//   - y doit être compris entre 0 et img->height - 1

void safe_put_pixel(mlx_image_t *image, int screen_x, int screen_y, uint32_t color_argb)
{
    if (screen_x >= 0 && screen_y >= 0 
        && screen_x < (int)image->width && screen_y < (int)image->height)
    {
        mlx_put_pixel(image, screen_x, screen_y, color_argb);
    }
}

