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
LIB_HOOKS		=	$(LIBS_DIR)/hooks
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
					minirt.c
HEAD_FILES		=	inc/minirt.h \
					inc/ggl_mlx_define.h \
					mlx/mlx.h
SRCS 			=	$(addprefix $(SRC_DIR)/,$(SRCS_FILES))
OBJS			=	$(addprefix $(OBJ_DIR)/,$(SRCS_FILES:.c=.o))
CFLAGS			=	-Wall -Wextra -Werror
LIBRARIES		=	$(LIB_FT)/libft.a $(LIB_V3D)/libv3d.a $(LIB_RGB)/librgb.a $(LIB_PARSER)/libparser.a $(LIB_SOLVER)/libsolvers.a $(LIB_HOOKS)/libhooks.a
INCLUDES		=	-I./mlx/mlx.h -I$(LIB_FT)/$(HEAD_DIR) -I$(LIB_V3D)/$(HEAD_DIR) -I$(LIB_RGB)/$(HEAD_DIR) -I$(LIB_PARSER)/$(HEAD_DIR) -I$(LIB_SOLVER)/$(HEAD_DIR) -I$(LIB_HOOKS)/$(HEAD_DIR) -I$(HEAD_DIR)
LIB_LINKS		=	-L./libs/lib -lft -L./libs/v3d -lv3d -L./libs/rgb -lrgb -L./libs/parser -lparser -L./libs/solvers -lsolvers -L./libs/hooks -lhooks -Lmlx -lmlx -framework OpenGL -framework AppKit
RM				=	rm -rf

#all: $(OBJ_SUBS) library $(NAME)
#
#$(NAME): $(OBJS) $(LIBRARIES)
#	$(CC) $(OBJS) $(CFLAGS) $(LIB_LINKS) -g -lm -o $(NAME)

all: $(OBJ_SUBS) library $(NAME)
	$(MAKE) CFLAGS="$(CFLAGS)" $(NAME)
	-rm -f .bonus

bonus: .bonus

.bonus: $(OBJ_SUBS)
	$(MAKE) LIB_DET=bonus library
	$(MAKE) CFLAGS="$(CFLAGS) -DBONUS" $(NAME)
	touch .bonus

# ... (Resto de tus reglas de construcción)

$(NAME): $(OBJS) $(LIBRARIES)
	@if [ -f .bonus ]; then \
		echo "Compiling bonus version"; \
	else \
		echo "Compiling normal version"; \
	fi
	$(CC) $(OBJS) $(CFLAGS) $(LIB_LINKS) -g -lm -o $(NAME)

library:
	$(MAKE) -C $(LIB_FT) $(LIB_DET)
	$(MAKE) -C $(LIB_V3D) $(LIB_DET)
	$(MAKE) -C $(LIB_RGB) $(LIB_DET)
	$(MAKE) -C $(LIB_PARSER) $(LIB_DET)
	$(MAKE) -C $(LIB_SOLVER) $(LIB_DET)
	$(MAKE) -C $(LIB_HOOKS) $(LIB_DET)
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
	$(MAKE) -C $(LIB_HOOKS) clean
	# $(MAKE) -C $(LIB_MLX) clean
	$(RM) $(MLX)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIB_FT) fclean
	$(MAKE) -C $(LIB_V3D) fclean
	$(MAKE) -C $(LIB_RGB) fclean
	$(MAKE) -C $(LIB_PARSER) fclean
	$(MAKE) -C $(LIB_SOLVER) fclean
	$(MAKE) -C $(LIB_HOOKS) fclean
	# $(MAKE) -C $(LIB_MLX) clean
	$(RM) $(NAME)
	$(RM) $(OBJ_SUBS)

memory: $(OBJ_SUBS) $(OBJS) $(HEAD_FILES)
	$(MAKE) CFLAGS+=-fsanitize=address re

#bonus: .bonus
#	$(MAKE) LIB_DET=bonus library
#	$(MAKE) CFLAGS+=-DBONUS

re:	fclean all

.PHONY: all clean fclean re
