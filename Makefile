# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/27 16:42:10 by mporras-          #+#    #+#              #
#    Updated: 2024/02/03 19:14:13 by vaguilar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#=-=-=-=-=-=-=- COLORS DEFINITION =-=-=-=-=-=-=-=-=-#

DEL_LINE		=	\033[2K
ITALIC			=	\033[3m
BOLD			=	\033[1m
DEF_COLOR		=	\033[0;39m
GRAY			=	\033[0;90m
RED				=	\033[0;91m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
BLUE			=	\033[0;94m
MAGENTA			=	\033[0;95m
CYAN			=	\033[0;96m
WHITE			=	\033[0;97m
BLACK			=	\033[0;99m
ORANGE			=	\033[38;5;209m
BROWN			=	\033[38;2;184;143;29m
DARK_GRAY		=	\033[38;5;234m
MID_GRAY		=	\033[38;5;245m
DARK_GREEN		=	\033[38;2;75;179;82
DARK_YELLOW		=	\033[38;5;143m

NAME			= 	miniRT

SRC_DIR			= 	srcs
OBJ_DIR			= 	objs
OBJ_SUBS		= 	objs \
					objs/utl \
					objs/sampler \
					objs/texture \
					objs/intersections \
					objs/rays \
					objs/light \
					objs/render
LIB_MLX			= 	mlx
LIBS_DIR		=	libs
LIB_FT			= 	$(LIBS_DIR)/lib
LIB_V3D			= 	$(LIBS_DIR)/v3d
LIB_RGB			=	$(LIBS_DIR)/rgb
LIBS_HEADERS	=	$(LIB_V3D)/inc/libft.h \
					$(LIB_V3D)/inc/v3d.h \
					$(LIB_RGB)/inc/rgb.h \
					$(LIB_MLX)/mlx.h
LIBS_LIBS		=	$(LIB_FT)/libft.a \
					$(LIB_V3D)/libv3d.a \
					$(LIB_RGB)/librgb.a
MODS_LIB		=	mod
MODS_PARSER		=	$(MODS_LIB)/parser
MODS_HOOKS		=	$(MODS_LIB)/hooks
MODS_SOLVERS	=	$(MODS_LIB)/solvers
MODS_HEADERS	=	$(MODS_PARSER)/inc/parse.h \
					$(MODS_HOOKS)/inc/hooks.h \
					$(MODS_SOLVERS)/inc/solvers.h
MODS_MODULES	=	$(MODS_PARSER)/libparser.a \
					$(MODS_HOOKS)/libhooks.a \
					$(MODS_SOLVERS)/libsolvers.a
MODS_BONUS		=	$(MODS_PARSER)/.bonus \
                    $(MODS_HOOKS)/.bonus \
                    $(MODS_SOLVERS)/.bonus
SRCS_FILES		= 	intersections/intersections.c \
					light/light.c \
					light/light_utils.c \
					rays/tracer.c \
					rays/rays.c \
					render/render_utils.c \
					render/render.c \
					utl/messenger.c \
					sampler/supersample.c \
					sampler/sample_pixel.c \
					texture/textures.c \
					texture/bump_texture.c \
					minirt.c
HEAD_FILES		=	inc/minirt.h \
					common/defines.h \
					common/objects.h \
					common/structs.h
INCLUDES_LIBS	:=	$(patsubst %,-I%,$(dir $(LIBS_HEADERS)))
INCLUDES_MODS	:=	$(patsubst %,-I%,$(dir $(MODS_HEADERS)))
INCLUDES_HEAD	:=	$(patsubst %,-I%,$(dir $(HEAD_FILES)))
SRCS 			=	$(addprefix $(SRC_DIR)/,$(SRCS_FILES))
OBJS			=	$(addprefix $(OBJ_DIR)/,$(SRCS_FILES:.c=.o))
CFLAGS			=	-Wall -Wextra -Werror
CFLAGS 			+=	-Wno-deprecated-declarations
LIBRARIES		=	$(LIBS_LIBS) $(MODS_MODULES)
INCLUDES		=	-Icommon $(INCLUDES_LIBS) $(INCLUDES_MODS) $(INCLUDES_HEAD)
LIB_LINKS		=	-L./$(LIB_FT) -lft -L./$(LIB_V3D) -lv3d -L./$(LIB_RGB) -lrgb -L./$(MODS_PARSER) -lparser -L./$(MODS_SOLVERS) -lsolvers -L./$(MODS_HOOKS) -lhooks -Lmlx -lmlx -framework OpenGL -framework AppKit
RM				=	rm -rf
BONUS_FILE		=	.bonus
CC				=	gcc
MAKE 			=	make --no-print-directory

all: version library modules $(OBJ_SUBS) $(NAME)

version:
	@if [ -f .bonus ]; then \
  		rm $(BONUS_FILE); \
		$(MAKE) fclean; \
		$(MAKE); \
	fi

bonus: CFLAGS += -DBONUS
bonus: LIB_DET = bonus
bonus: version_bonus library modules
bonus: $(OBJ_SUBS) $(NAME) $(BONUS_FILE)

version_bonus:
	@if [ ! -f $(BONUS_FILE) ] && [ -f $(NAME) ]; then \
		$(MAKE) fclean; \
    fi

$(BONUS_FILE):
	@touch .bonus

$(NAME): $(OBJS) $(HEAD_FILES) $(LIBRARIES)
	@$(CC) $(OBJS) $(CFLAGS) $(LIB_LINKS) -g -lm -o $(NAME)
	@echo "$(MAGENTA)Executable $@ compiled$(DEF_COLOR)"

library:
	@echo "$(YELLOW)Building LIBRARIES$(DEF_COLOR)"
	@echo "$(YELLOW)------------------$(DEF_COLOR)"
	@echo "$(YELLOW)Building LIBFT$(DEF_COLOR)" ; echo
	@$(MAKE) -C $(LIB_FT)
	@echo "$(YELLOW)Building V3D$(DEF_COLOR)"
	@$(MAKE) -C $(LIB_V3D)
	@echo "$(YELLOW)Building RGB$(DEF_COLOR)"
	@$(MAKE) -C $(LIB_RGB)
	@echo "$(YELLOW)Building MLX$(DEF_COLOR)"
#	$(MAKE) -C $(LIB_MLX)

modules:
	@echo "$(YELLOW)Building MODULES" $(LIB_DET) "$(DEF_COLOR)"
	@echo "$(YELLOW)----------------------$(DEF_COLOR)"
	@echo "$(YELLOW)Building PARSER MODULE$(DEF_COLOR)"
	@$(MAKE) -C $(MODS_PARSER) $(LIB_DET)
	@echo "$(YELLOW)Building HOOKS MODULE$(DEF_COLOR)"
	@$(MAKE) -C $(MODS_HOOKS) $(LIB_DET)
	@echo "$(YELLOW)Building SOLVERS MODULE$(DEF_COLOR)"
	@$(MAKE) -C $(MODS_SOLVERS) $(LIB_DET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@
	@echo "$(GREEN)$(patsubst $(SRCS_DIR)/%,%, $<)" | awk '{printf "%-50s\tcompiled ✓$(DEF_COLOR)\n", $$0;}'


$(OBJ_SUBS):
	@-mkdir $(OBJ_SUBS)

clean:
	@$(MAKE) -C $(LIB_FT) clean
	@$(MAKE) -C $(LIB_V3D) clean
	@$(MAKE) -C $(LIB_RGB) clean
	@$(MAKE) -C $(MODS_SOLVERS) clean
	@$(MAKE) -C $(MODS_PARSER) clean
	@$(MAKE) -C $(MODS_HOOKS) clean
#	@$(MAKE) -C $(LIB_MLX) clean
	@$(RM) $(MLX)
	@$(RM) $(OBJS)
	@echo "$(RED)All temporary objects removed successfully${DEF_COLOR}"

fclean: clean
	@$(MAKE) -C $(LIB_FT) fclean
	@$(MAKE) -C $(LIB_V3D) fclean
	@$(MAKE) -C $(LIB_RGB) fclean
	@$(MAKE) -C $(MODS_SOLVERS) fclean
	@$(MAKE) -C $(MODS_PARSER) fclean
	@$(MAKE) -C $(MODS_HOOKS) fclean
#	@$(MAKE) -C $(LIB_MLX) clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ_SUBS)
	@$(RM) $(BONUS_FILE)
	@echo "$(RED)Executable have been fully cleaned${DEF_COLOR}"

memory: $(OBJ_SUBS) $(OBJS) $(HEAD_FILES)
	@$(MAKE) CFLAGS+=-fsanitize=address re
	@echo "$(RED)Executable have been fully cleaned${DEF_COLOR}"
	
re:	fclean all

.PHONY: all clean fclean re
