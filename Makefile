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
					objs/parser \
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
LIB_MLX			= 	mlx
SRCS_FILES		= 	intersections/sphere.c \
					intersections/plane.c \
					intersections/square.c \
					intersections/triangle.c \
					intersections/cylinder.c \
					intersections/pyramid.c \
					intersections/cube.c \
					intersections/intersections.c \
					light/light.c \
					rays/tracer.c \
					rays/rays.c \
					render/render.c \
					parser/readfile.c \
					parser/parser_builders.c \
					parser/parser_utils.c \
					parser/parser_rgb.c \
					parser/parser_v3d.c \
					parser/sphere.c \
					parser/plane.c \
					parser/cylinder.c \
					parser/square.c \
					parser/triangle.c \
					parser/cube.c \
					parser/pyramid.c \
					parser/parser_resolution.c \
					parser/parser_ambient.c \
					parser/parser_camera.c \
					parser/parser_light.c \
					utl/utilities.c \
					utl/error_handling.c \
					sampler/supersample.c \
					sampler/sample_pixel.c \
					texture/textures.c \
					minirt.c \
					debug_print.c
HEAD_FILES		=	inc/minirt.h \
					inc/ggl_mlx_define \
					mlx/mlx.h
SRCS 			=	$(addprefix $(SRC_DIR)/,$(SRCS_FILES))
OBJS			=	$(addprefix $(OBJ_DIR)/,$(SRCS_FILES:.c=.o))
CFLAGS			=	-Wall -Wextra -Werror
INCLUDES		=	-I./mlx/mlx.h -I$(LIB_FT)/$(HEAD_DIR) -I$(LIB_V3D)/$(HEAD_DIR) -I$(LIB_RGB)/$(HEAD_DIR) -I$(HEAD_DIR)
LIB_LINKS		=	-L./libs/lib -lft -L./libs/v3d -lv3d -L./libs/rgb -lrgb -Lmlx -lmlx -framework OpenGL -framework AppKit 
RM				=	rm -rf

# ---------------------
# -----------------------
all: $(OBJ_SUBS) library $(NAME)


$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIB_LINKS) -g -lm -o $(NAME)

library:
	$(MAKE) -C $(LIB_FT)
	$(MAKE) -C $(LIB_V3D)
	$(MAKE) -C $(LIB_RGB)
	# $(MAKE) -C $(LIB_MLX)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

$(OBJ_SUBS):
	-mkdir $(OBJ_SUBS)

clean:
	$(MAKE) -C $(LIB_FT) clean
	$(MAKE) -C $(LIB_V3D) clean
	$(MAKE) -C $(LIB_RGB) clean
	# $(MAKE) -C $(LIB_MLX) clean
	$(RM) $(MLX)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIB_FT) fclean
	$(MAKE) -C $(LIB_V3D) fclean
	$(MAKE) -C $(LIB_RGB) fclean
	# $(MAKE) -C $(LIB_MLX) clean
	$(RM) $(NAME)
	$(RM) $(OBJ_SUBS)

bonus: clean
	$(eval CFLAGS += -DBONUS=1)
	echo $CFLAGS
	$(MAKE) all

re:	fclean all

.PHONY: all clean fclean re
