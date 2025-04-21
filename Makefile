# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alpha <alpha@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 19:37:41 by alpha             #+#    #+#              #
#    Updated: 2025/04/21 20:26:18 by alpha            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# Source files
SRC_DIR = src
SRC_FILES = main.c vector.c objects.c light.c parser.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Header files
INC_DIR = inc
INCS = $(INC_DIR)/minirt.h

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

# Determine OS for proper linking
UNAME := $(shell uname)

# MiniLibX location and flags
MLX_DIR = lib/mlx_linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)

# OS-specific flags
ifeq ($(UNAME), Linux)
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(UNAME), Darwin)
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
    $(error Unsupported operating system: $(UNAME))
endif

# GNL add
SRC_GNL_DIR = lib/gnl
SRC_GNL = get_next_line.c get_next_line_utils.c
SRCS_GNL = $(addprefix $(SRC_GNL_DIR)/, $(SRC_GNL))
OBJS_GNL = $(addprefix $(OBJ_DIR)/, $(SRC_GNL:.c=.o))

# Rules
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_GNL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(OBJS_GNL)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_GNL) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Install MiniLibX (Linux)
install_mlx_linux:
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)
	make -C $(MLX_DIR)

# Install MiniLibX (macOS)
install_mlx_macos:
	git clone https://github.com/pbondoer/MinilibX.git $(MLX_DIR)
	make -C $(MLX_DIR)

# Create the get_next_line directory and files
setup_gnl:
	mkdir -p $(SRC_GNL_DIR)
	touch $(SRC_GNL_DIR)/get_next_line.c
	touch $(SRC_GNL_DIR)/get_next_line_utils.c
	touch $(SRC_GNL_DIR)/get_next_line.h

# Run the program with a scene file
run: all
	./$(NAME) scenes/basic.rt

.PHONY: all clean fclean re install_mlx_linux install_mlx_macos setup_gnl run

