# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 13:52:24 by eel-abed          #+#    #+#              #
#    Updated: 2025/05/03 20:01:04 by eel-abed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = lib/LIBFT_WITH_BONUS-master
MLX_DIR = lib/minilibx-linux
GNL_DIR = lib/Get_next_line

# Fichiers source
SRC = 	src/main.c \
		src/parsing/parse_map.c \
		src/parsing/parse_textures.c \
		src/parsing/parse_grid.c \
		src/parsing/parse_colors.c \
		src/parsing/parse_file.c\
		src/parsing/validate_map.c\
		src/parsing/parsing_utils.c\
		lib/Get_next_line/get_next_line.c

# Fichiers objet
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Chemins d'inclusion
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR)

# Bibliothèques pour la liaison
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Règles
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBS) -o $(NAME)
	@echo "$(NAME) created!"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/lib/%.o: lib/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed!"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(NAME) removed!"

re: fclean all

.PHONY: all clean fclean re
