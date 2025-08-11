# === PATHS ===

# Dossier des fichiers objets pour cub3D
BUILD_DIR = object

# Dossier de la MLX42 (CodeAM)
MLX_PATH = ./MLX42

# Dossier de la libft
LIBFT_PATH = ./libft

# === FILES ===

# Nom de l'exécutable
NAME = cub3D

# Liste des fichiers sources .c
SRC = cub3d.c \
cleanup.c \
./init/validate_input.c \
./init/sanitize_structs.c \
./init/simulation_config.c \
./parsing/map_data_manager.c \
./parsing/config/extract_config.c \
./parsing/config/set_texture.c \
./parsing/config/set_color.c \
./parsing/map/map_dimensions.c \
./parsing/map/map_copy.c \
./parsing/map/map_validation.c \
./parsing/map/map_closure.c \
./parsing/config/validate_config.c \
./parsing/utils/parsing_utils.c \
./parsing/utils/error_handling.c \
./resources/resources_manager.c \
./resources/player_orientation.c \
./resources/color_conversion.c \
./resources/texture_loader.c \
./resources/resources_free.c \
./engine/screen_manager.c \
./engine/engine_loop.c \
./engine/raycasting/render.c \
./engine/raycasting/prepare.c \
./engine/raycasting/dda.c \
./engine/raycasting/texture.c \
./engine/raycasting/draw.c \
./engine/raycasting/utils.c \
./game/input_handler.c \
./game/player_movement.c \
./game/map_collision.c \
./bonus/compass.c \
./bonus/compass_utils.c \
./bonus/compass_draw.c




# === OBJECTS ===

# Transformation des fichiers .c en fichiers objets .o + placés dans le dossier build
OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC))



# === COMPILATION ===

# Compilateur (conforme au sujet)
CC = cc

# Flags de compilation (conforme au sujet)
CFLAGS = -Wall -Wextra -Werror -O3


# Librairies nécessaires à la MLX42 (les flags viennent d'ici : https://github.com/codam-coding-college/MLX42)

# ecole :
MLX_LIBS = $(MLX_PATH)/build/libmlx42.a -ldl -lglfw -pthread -lm
# maison : 
# MLX_LIBS = ./MLX42/build/libmlx42.a ./MLX42/build/_deps/glfw-build/src/libglfw3.a -lX11 -ldl -pthread -lm

# Inclusion des headers (MLX, libft, et headers a nous)
# HEADERS = -I. -Isrcs -I$(MLX_PATH)/include -I$(LIBFT_PATH)
HEADERS = -I$(MLX_PATH)/include -I$(LIBFT_PATH) -Isrcs




# === REGLES PRINCIPALES ===

# Compilation complète
all: $(BUILD_DIR) libmlx libft $(NAME)

# Création du dossier build_cub3d si nécessaire
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compilation de la libft si elle n'est pas encore construite
$(LIBFT_PATH)/libft.a:
	@$(MAKE) -C $(LIBFT_PATH)

# Raccourci pour rendre la règle phony (au cas ou mais ici inutile)
libft: $(LIBFT_PATH)/libft.a

# Compilation de la MLX42 (CodeAM)
libmlx:
	@chmod +x $(MLX_PATH)/tools/compile_shader.sh
	@cmake -S $(MLX_PATH) -B $(MLX_PATH)/build
	@cmake --build $(MLX_PATH)/build -j4

# Compilation finale de l'exécutable cub3D
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIBS) $(LIBFT_PATH)/libft.a $(HEADERS) -o $(NAME)


# Compilation des fichiers .c en .o
# PS : 42 autorise totalement ce genre de règles car elles ne détectent pas les fichiers automatiquement, elles les transforment juste.
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@



# === REGLES DE NETTOYAGE ===

# Supprime les fichiers objets et build de la MLX
clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(MLX_PATH)/build

# Nettoyage complet (exécutable en +)
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

# Recompilation
re: fclean all



# === PHONY ===

# Déclare les règles comme étant toujours exécutables même si un fichier du même nom existe deja
.PHONY: all clean fclean re libmlx libft
