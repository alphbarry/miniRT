# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alpha <alpha@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 19:37:41 by alpha             #+#    #+#              #
#    Updated: 2025/05/16 22:54:00 by alpha            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#<--------------------------------->COLORS<----------------------------------->#
DEF_COLOR	=	\033[1;99m
WHITE_BOLD	=	\033[1m
BLACK		=	\033[1;90m
RED			=	\033[1;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[1;94m
PINK		=	\033[1;95m
CIAN		=	\033[1;96m

#<--------------------------------->NAME<------------------------------------>#
NAME		=	miniRT

#<-------------------------------->LIBRARY<---------------------------------->#
LIBRARY		=	lib/
LIB_A		=	lib/libft/libft.a lib/gnl/libgnl.a \
				lib/mlx_linux/libmlx.a
LIB_SEARCH	=	-L./lib/libft -L./lib/gnl -L./lib/mlx_linux
MLXLIB		=	lib/mlx_linux/libmlx.a -lXext -lX11 -lm -lz

#<-------------------------------->HEADERS<---------------------------------->#
HEADER		=	./inc/
GNL_H	    =   ./lib/gnl/
LIBFT_H		=	./lib/libft/
MLX_H		=	./lib/mlx_linux/

#<--------------------------------->DIRS<------------------------------------>#
SRC_DIR		=	src/
OBJ_DIR		=	objects/

#<--------------------------------->FILES<---------------------------------->#
FILES		=	main.c \
				parser/parser_ambient.c \
				parser/parser_camera.c \
				parser/parser_light.c \
				parser/parser_light_utils.c \
				parser/parser_cylinder.c \
				parser/parser_cylinder_utils.c \
				parser/parser_plane.c \
				parser/parser_plane_utils.c \
				parser/parser_sphere.c \
				parser/parser_sphere_utils.c \
				parser/parser_validation.c \
				parser/read_scene.c \
				parser/init_params.c \
				utils/free.c \
				window/mlx.c \
				window/keys.c \
				window/window_size.c \
				colors/colors.c \
				raytracing/vectors.c \
				raytracing/raytrace.c \
				figures/cylinders.c \
				figures/planes.c \
				figures/spheres.c \
				environment/light.c
#<--------------------------------->SRCS<----------------------------------->#
SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

#<----------------------------->OBJS && DEPS<------------------------------->#
OBJS		=	$(addprefix $(OBJ_DIR), $(subst .c,.o,$(FILES)))
DEPS		=	$(subst .o,.d,$(OBJS))

#<-------------------------------->COMANDS<---------------------------------->#
INCLUDE		=	-I$(HEADER) -I$(PRINTF_H) -I$(LIBFT_H) -I$(MLX_H)
RM			=	rm -rf
MKD			=	mkdir -p
MK			=	Makefile
CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address
MKFLAGS		=	--no-print-directory

#<--------------------------------->RULES<----------------------------------->#
$(OBJ_DIR)%.o	:$(SRC_DIR)%.c $(LIB_A) $(MK)
	@$(MKD) $(dir $@)
	@printf "$(PINK)    \rCompiling: $(YELLOW)$(notdir $<)...$(DEF_COLOR)       \r"
	@$(CC) -MT $@ $(CFLAGS) -MMD -MP $(INCLUDE) -c $< -o $@

all				:
	@$(MAKE) $(MKFLAGS) -C $(LIBRARY)
	@$(MAKE) $(MKFLAGS) $(NAME)


$(NAME)			:	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_A) $(MLXLIB) -o $@
	@echo "\n$(GREEN)miniRT has been compiled$(DEF_COLOR)"

clean			:
	@$(MAKE) $(MKFLAGS) clean -C $(LIBRARY)
	@$(RM) $(OBJ_DIR) $(B_OBJ_DIR)
	@echo ""
	@echo "$(RED)All OBJS && DEPS has been removed$(DEF_COLOR)"
	@echo ""

fclean			:
	@$(MAKE) $(MKFLAGS) clean
	@$(MAKE) $(MKFLAGS) fclean -C $(LIBRARY)
	@$(RM) $(NAME) $(B_NAME)
	@echo ""
	@echo "$(RED)Program has been removed$(DEF_COLOR)"

re				:
	@$(MAKE) $(MKFLAGS) fclean
	@$(MAKE) $(MKFLAGS) all
	@echo ""
	@echo "$(CIAN)miniRT has been recompiled$(DEF_COLOR)"

.PHONY			: all clean fclean re

-include		$(DEPS)
