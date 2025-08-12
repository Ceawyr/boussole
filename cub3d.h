/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnamoune <cnamoune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:41:06 by mwallis           #+#    #+#             */
/*   Updated: 2025/08/12 18:40:02 by cnamoune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H


# include <fcntl.h>    // --> open
# include <limits.h>   // --> INT_MIN, INT_MAX
# include <math.h>     //--> sin, cos, fabs
# include "libft.h"
# include "MLX42/MLX42.h"


// DEJA DANS LA LIBFT, donc pas besoin de remettre car on les include deja libft.h :
// # include <unistd.h>         --> read, write, close, access (Vérifier l’existence/droits d’un fichier), fork ,pipe, dup, dup2, execve, getcwd etc...
// # include <stdlib.h>         --> malloc, free, exit, rand, qsort
// # include <stdio.h>          --> printf (uniquement pour debug, j'ai pas mis le notre), perror
// # include <stdint.h>         --> uint8_t	(entier non signé sur 8 bits, 0 à 255), uintptr_t (entier capable de contenir une adresse)
// # include <sys/select.h>     --> FD_SETSIZE	(Valeur max des fd gérables par select() (souvent 1024)) pour GNL




typedef struct s_map_data
{
    // Map
	char	**map;
	int		map_width;
	int		map_height;

	// Couleurs
	int		floor_color[3];
    int     is_floor_already_defined;
	int		ceiling_color[3];
    int     is_ceiling_already_defined;

    // Textures
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;

	// Joueur au tout debut
	char	player_direction;
	double	player_x_start;
	double	player_y_start;

}   t_map_data;



typedef struct s_player_data
{
	/* position du joueur */
    double  position_x;
    double  position_y;

	/* vecteur direction (longueur 1)  */
    double  direction_x;
    double  direction_y;

	/* vecteur plan caméra (FOV=66°)   */
    double  plane_x;
    double  plane_y;

}	t_player_data;




typedef struct s_player_speed_config
{
	double	linear;
	double	lateral;
}	t_player_speed_config;


typedef struct s_camera_config
{
	double	rotation_speed;
	// double	fov;
}	t_camera_config;


typedef struct s_dimensions_config
{
	int32_t	screen_width;
	int32_t	screen_height;
	int		texture_width;
	int		texture_height;
}	t_dimensions_config;



typedef struct s_resources
{	
	mlx_t			*mlx;
	mlx_image_t		*north_image;
	mlx_image_t		*south_image;
	mlx_image_t		*west_image;
	mlx_image_t		*east_image;
	mlx_image_t		*screen;
	mlx_image_t		*compass_background;
	mlx_image_t		*compass_needle;

	// mlx_window_t *win;	// optionnel, si jamais tu veux manipuler la fenetre pour faire une victoire a la fin d'un labyrinth

	uint32_t				floor_argb;
	uint32_t				ceiling_argb;

	t_map_data				map_data;
	t_player_data			player_data;
	t_player_speed_config	player_speed_config;
	t_camera_config			camera_config;
	t_dimensions_config		dimensions_config;
	
}	t_resources;



typedef struct s_raycast_data
{
    double  ray_direction_x;          // Direction du rayon en X
    double  ray_direction_y;          // Direction du rayon en Y

    int     ray_current_tile_x;       // Case actuelle du rayon (X)
    int     ray_current_tile_y;       // Case actuelle du rayon (Y)

    double  dist_to_next_x;           // Distance jusqu’à la prochaine ligne verticale
    double  dist_to_next_y;           // Distance jusqu’à la prochaine ligne horizontale

    double  dist_per_tile_x;          // Distance pour franchir une case en X
    double  dist_per_tile_y;          // Distance pour franchir une case en Y

    int     advance_direction_x;      // Sens du pas en X (-1 = gauche, +1 = droite)
    int     advance_direction_y;      // Sens du pas en Y (-1 = haut, +1 = bas)

    int     hit_side;                 // 0 = mur vertical (NS), 1 = mur horizontal (EW)
    double  perp_distance;            // Distance perpendiculaire au mur

} t_raycast_data;




typedef struct s_ray_column_norm_helper
{
    mlx_image_t  *texture;
	int           wall_start_y;
	int           wall_end_y;
	int           wall_height_in_pixels;
	int           wall_hit_x;

}	t_ray_column_norm_helper;


typedef struct s_needle_data
{
	double	cos_angle;
	double	sin_angle;
	int		half_width;
	int		half_height;
}	t_needle_data;

typedef struct s_compass_pos
{
	int	compass_x;
	int	compass_y;
	int	center_x;
	int	center_y;
}	t_compass_pos;







# define ERROR_ARGC "\033[91mError\nThis program takes a single argument as \
parameter.\033[0m\n"

# define ERROR_CUB "\033[91mError\nThis program takes a .cub map file as \
parameter.\033[0m\n"

# define ERROR_OPEN "\033[91mError\nError while opening file.\033[0m\n"

# define ERROR_EMPTY_FILE "\033[91mError\nThe file is empty.\033[0m\n"

# define ERROR_UNKNOWN_IDENTIFIER "\033[91mError\nInvalid or unknown \
identifier found in .cub file. Expected: NO, SO, WE, EA, F, C, or map \
data. Ensure the map is a single, closed block surrounded by walls \
(1).\033[0m\n"

# define ERROR_MISSING_TEXTURE_PATH "\033[91mError\nMissing path after \
texture identifier. Expected one or more spaces followed by a valid \
texture path.\033[0m\n"

# define ERROR_ALLOC "\033[91mError\nMemory allocation failed.\033[0m\n"

# define ERROR_TEXTURE_PATH_EMPTY "\033[91mError\nTexture path is empty. \
Expected a valid path after identifier (e.g. NO ./path_to_texture).\033[0m\n"

# define ERROR_DUPLICATE_TEXTURE "\033[91mError\nDuplicate texture path \
detected. Each texture (NO, SO, WE, EA) must be defined only once in the \
.cub file.\033[0m\n"

# define ERROR_MISSING_COLOR_VALUE "\033[91mError\nMissing value after \
color identifier. Expected one or more spaces followed by a valid RGB \
value.\033[0m\n"

# define ERROR_DUPLICATE_COLOR "\033[91mError\nDuplicate color detected. \
Each color (F or C) must be defined only once in the .cub file.\033[0m\n"

# define ERROR_INVALID_RGB "\033[91mError\nInvalid RGB color format. \
Expected format: R,G,B with values between 0 and 255.\033[0m\n"

# define ERROR_MAP_NOT_SINGLE_BLOCK "\033[91mError\nMap is not a single \
block. Unexpected map content after map ended.\033[0m\n"

# define ERROR_MAP_NOT_AT_THE_END "\033[91mError\nInvalid map position in \
.cub file.\nThe map must appear at the end of the file.\033[0m\n"

# define ERROR_INVALID_CHAR "\033[91mError\nThe map contains an invalid \
character.\nOnly the following characters are allowed:\n'0' (floor), \
'1' (wall), 'N', 'S', 'E', 'W' (player directions).\033[0m\n"

# define ERROR_NUMBER_CHARACTER "\033[91mError\nInvalid number of player \
starting positions.\nThe map must contain exactly one starting position \
among the characters: 'N', 'S', 'E', or 'W'.\033[0m\n"

# define ERROR_MAP_TOO_SMALL "\033[91mError\nThe map is too \
small.\nMinimum required size is:\n  - 4x4\n  - or 3x5\n  - or 5x3\nEnsure \
your map meets one of these minimum dimensions.\033[0m\n"

#define ERROR_MAP_NOT_CLOSED "\033[91mError\nThe map is not closed. \
Player can escape through a hole or space.\033[0m\n"

#define ERROR_EMPTY_MAP "\033[91mError\nMap data is missing or empty \
in the .cub file.\nExpected a map layout defined with characters: \
'1', '0', 'N', 'S', 'E', 'W'.\033[0m\n"

#define ERROR_MISSING_CONFIG "\033[91mError\nIncomplete configuration \
in .cub file.\nMissing one or more required elements: textures \
(NO, SO, WE, EA) or colors (F, C).\033[0m\n"

#define ERROR_TEXTURE_PATH_NULL "\033[91mError\nA texture path is missing. \
All texture paths (NO, SO, WE, EA) must be defined.\033[0m\n"

#define ERROR_TEXTURE_NOT_ACCESSIBLE_START "\033[91mError\nCannot access \
texture file : \033[0m"

#define ERROR_TEXTURE_NOT_ACCESSIBLE_END "\033[91m\nMake sure the path \
exists and is readable.\033[0m\n"

#define ERROR_TEXTURE_NOT_PNG "\033[91mError\nTexture file must be a \
.png file. Expected extension: .png\033[0m\n"

# define ERROR_MLX_INIT "\033[91mError\nFailed to initialize MLX.\n\
Ensure that your system supports MLX42 and try again.\033[0m\n"

# define ERROR_LOAD_TEXTURE "\033[91mError\nFailed to load a texture.\n\
Check the file path and ensure the image exists and is valid.\033[0m\n"

# define ERROR_LOAD_IMAGE "\033[91mError\nFailed to convert texture to image.\n\
Ensure MLX is properly initialized and your textures are valid.\033[0m\n"

#define ERROR_NEW_IMAGE "\033[91mError\nFailed to create a new image.\n\
Ensure MLX is properly initialized and sufficient memory is available.\033[0m\n"

#define ERROR_DISPLAY_IMAGE "\033[91mError\nFailed to display image in the \
window.\nEnsure MLX is initialized and the window is valid.\033[0m\n"

#define ERROR_SCREEN_NOT_INITIALIZED "\033[91mError\nScreen buffer is not \
initialized.\nCall init_screen() before rendering frames.\033[0m\n"

#define INFO_ESCAPE_EXIT "\033[96m[EXIT] Escape key pressed.\n" \
"Application terminated gracefully.\n" \
"Resources have been released.\033[0m\n"

#define INFO_WINDOW_CLOSE "\033[96m[EXIT] Window closed by user.\n" \
"Application terminated gracefully.\n" \
"Resources have been released.\033[0m\n"




void validate_input(int argc, char *argv[]);

void	sanitize_structs(t_resources *resources);

void init_simulation_parameters(t_resources *resources);


void init_map_data(char *map, t_map_data *map_data);



void get_map_config(int fd, t_map_data *map_data);

void    get_north_texture_path(char *line, t_map_data *map_data, int fd, char *line_origin);
void    get_south_texture_path(char *line, t_map_data *map_data, int fd, char *line_origin);
void    get_west_texture_path(char *line, t_map_data *map_data, int fd, char *line_origin);
void    get_east_texture_path(char *line, t_map_data *map_data, int fd, char *line_origin);

void get_floor_color(char *line, t_map_data *map_data, int fd, char *line_origin);
void get_ceiling_color(char *line, t_map_data *map_data, int fd, char *line_origin);

void	get_map_dimensions(int fd, t_map_data *map_data);

void copy_map(int fd, t_map_data *map_data);

void    check_map_validity(t_map_data *map_data);
char	**duplicate_map(t_map_data *map_data);
void	flood_fill(char **map_copy, int x, int y, t_map_data *map_data);





void	ensure_config_ready(t_map_data *map_data);






void	*malloc_filled_with_space(size_t nmemb, size_t size);
int     skip_white_space(char *str);
int     ft_atoi_with_validation(const char *nptr, int *is_valid);
void    free_tab_rgb(char **tab);



void	clear_remaining_lines_gnl(int fd);
void    free_residual_line_and_gnl(int fd, char **line);
void    free_map_copy(char **map_copy);
void	write_close_and_exit(int fd, const char *str, t_map_data *map_data);


















void	init_game_data(t_resources	*resources);
void	set_player_orientation(t_resources	*resources);
void set_floor_and_ceiling_colors(t_resources *resources);
mlx_image_t	*load_image_texture(t_resources	*resources, const char *path);


void	free_game_resources(t_resources	*resources);





void    init_screen(t_resources *resources);
void	engine_loop(void *setting);


void render_frame(void *setting);
void init_raycast(const t_resources *resources, int screen_x, t_raycast_data *ray);
void raycast_digital_differential_analyzer(const t_resources *resources, t_raycast_data *ray);
mlx_image_t *determine_texture_and_hit_column(const t_resources *resources, const t_raycast_data *ray, int *wall_hit_x);
void draw_entire_pixel_column(t_resources *resources, int screen_x, const t_raycast_data *ray, t_ray_column_norm_helper *helper);

uint32_t convert_rgba_to_argb(const mlx_image_t *image, int x, int y);
uint32_t shade_color(uint32_t color);
void safe_put_pixel(mlx_image_t *image, int screen_x, int screen_y, uint32_t color_argb);







void	handle_keypress_input(t_resources *resources);
void move_player_rotation(t_player_data *player_data, double angle);
void move_player_linear(t_player_data *player_data, t_map_data *map_data, double linear_speed, int direction);
void move_player_lateral(t_player_data *player_data, t_map_data *map_data, double lateral_speed, int direction);
void attempt_player_move(t_player_data *player_data, t_map_data *map_data, double delta_x, double delta_y);






void	free_map_data(t_map_data *map_data);
void	write_and_exit_error(const char *str, t_map_data *map_data);
void	write_and_exit_with_graphics_error(const char *str, t_resources *resources);

void		init_compass(t_resources *resources);
void		render_compass(t_resources *resources);
void		free_compass_resources(t_resources *resources);
uint32_t	get_pixel_safe(mlx_image_t *img, int x, int y);
double		calculate_player_angle(const t_player_data *player);


#endif
