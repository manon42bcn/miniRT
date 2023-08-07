# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/27 16:42:10 by mporras-          #+#    #+#              #
#    Updated: 2023/06/23 17:24:38 by mporras-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	miniRT
HEAD_DIR		= 	inc
SRC_DIR			= 	srcs
OBJ_DIR			= 	objs
OBJ_SUBS		= 	objs \
					objs/hooks \
					objs/utl \
					objs/sampler \
					objs/texture \
					objs/intersections \
					objs/rays \
					objs/light \
					objs/render
LIBS_DIR		=	libs
LIB_FT			= 	$(LIBS_DIR)/lib
LIB_V3D			= 	$(LIBS_DIR)/v3d
LIB_RGB			=	$(LIBS_DIR)/rgb
LIB_PARSER		=	$(LIBS_DIR)/parser
LIB_SOLVER		=	$(LIBS_DIR)/solvers
LIB_MLX			= 	mlx
SRCS_FILES		= 	intersections/intersections.c \
					light/light.c \
					rays/tracer.c \
					rays/rays.c \
					render/mlx_hooks.c \
					render/render.c \
					utl/error_handling.c \
					sampler/supersample.c \
					sampler/sample_pixel.c \
					texture/textures.c \
					hooks/cylinder_hooks.c \
					hooks/main_hooks.c \
					hooks/mouse_handler.c \
					hooks/sphere_hooks.c \
					minirt.c
HEAD_FILES		=	inc/minirt.h \
					inc/ggl_mlx_define.h \
					mlx/mlx.h
SRCS 			=	$(addprefix $(SRC_DIR)/,$(SRCS_FILES))
OBJS			=	$(addprefix $(OBJ_DIR)/,$(SRCS_FILES:.c=.o))
CFLAGS			=	-Wall -Wextra -Werror
INCLUDES		=	-I./mlx/mlx.h -I$(LIB_FT)/$(HEAD_DIR) -I$(LIB_V3D)/$(HEAD_DIR) -I$(LIB_RGB)/$(HEAD_DIR) -I$(LIB_PARSER)/$(HEAD_DIR) -I$(LIB_SOLVER)/$(HEAD_DIR) -I$(HEAD_DIR)
LIB_LINKS		=	-L./libs/lib -lft -L./libs/v3d -lv3d -L./libs/rgb -lrgb -L./libs/parser -lparser -L./libs/solvers -lsolvers -Lmlx -lmlx -framework OpenGL -framework AppKit
RM				=	rm -rf
#CFLAGS += -fsanitize=address

all: $(OBJ_SUBS) library $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIB_LINKS) -g -lm -o $(NAME)

library:
	$(MAKE) -C $(LIB_FT) $(LIB_DET)
	$(MAKE) -C $(LIB_V3D) $(LIB_DET)
	$(MAKE) -C $(LIB_RGB) $(LIB_DET)
	$(MAKE) -C $(LIB_PARSER) $(LIB_DET)
	$(MAKE) -C $(LIB_SOLVER) $(LIB_DET)
	# $(MAKE) -C $(LIB_MLX)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

$(OBJ_SUBS):
	-mkdir $(OBJ_SUBS)

clean:
	$(MAKE) -C $(LIB_FT) clean
	$(MAKE) -C $(LIB_V3D) clean
	$(MAKE) -C $(LIB_RGB) clean
	$(MAKE) -C $(LIB_PARSER) clean
	$(MAKE) -C $(LIB_SOLVER) clean
	# $(MAKE) -C $(LIB_MLX) clean
	$(RM) $(MLX)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIB_FT) fclean
	$(MAKE) -C $(LIB_V3D) fclean
	$(MAKE) -C $(LIB_RGB) fclean
	$(MAKE) -C $(LIB_PARSER) fclean
	$(MAKE) -C $(LIB_SOLVER) fclean
	# $(MAKE) -C $(LIB_MLX) clean
	$(RM) $(NAME)
	$(RM) $(OBJ_SUBS)

memory: $(OBJ_SUBS) $(OBJS) $(HEAD_FILES)
	$(MAKE) CFLAGS+=-fsanitize=address re

bonus: fclean
	$(MAKE) LIB_DET=bonus library
	$(MAKE) CFLAGS+=-DBONUS



re:	fclean all

.PHONY: all clean fclean re
