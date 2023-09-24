
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 20:09:37 by mporras-          #+#    #+#              #
#    Updated: 2022/01/19 12:39:38 by mporras-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	builders.c \
				cleaners.c \
				cylinder.c \
				parser_ambient.c \
				parser_builders.c \
				parser_camera.c \
				parser_light.c \
				parser_resolution.c \
				parser_rgb.c \
				parser_utils.c \
				parser_v3d.c \
				plane.c \
				readfile.c \
				sphere.c \
				square.c \
				triangle.c \
				cube.c \
				pyramid.c \
				cone.c \
				hyperboloid.c \
				paraboloid.c \
				ellipsoid.c
SRCS_DIR	=	srcs
OBJS_DIR	=	obj
OBJS 		=	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
OBJS_SUBS	= 	obj
CC			=	gcc
RM			=	@rm -rf
NAME		=	libparser.a
HEADER		=	inc/parse.h \
				inc/parse_enum.h \
				../../libs/v3d/inc/v3d.h \
				../../libs/rgb/inc/rgb.h \
				../../libs/lib/inc/libft.h \
				../../inc/objects.h \
				../../inc/structs.h \
				../../inc/defines.h
BONUS_FILE	= .bonus
CFLAGS 		=	-Wall -Wextra -Werror
INCLUDES	:=	$(patsubst %,-I%,$(dir $(HEADER)))

all: version $(NAME) $(HEADER)

version:
	@if [ -f .bonus ]; then \
  		rm $(BONUS_FILE); \
		$(MAKE) fclean; \
		$(MAKE); \
	fi

$(NAME): $(OBJS_DIR) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

$(OBJS_DIR):
	-@mkdir $(OBJS_DIR)

bonus: CFLAGS += -DBONUS
bonus: version_bonus $(BONUS_FILE)

version_bonus:
	@if [ ! -f $(BONUS_FILE) ] && [ -f $(NAME) ]; then \
		$(MAKE) fclean; \
    fi

$(BONUS_FILE): $(OBJS_DIR) $(OBJS)
	ar rcs $(NAME) $(OBJS)
	touch $(BONUS_FILE)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_DIR) $(OBJS_B_DIR)
	$(RM) $(BONUS_FILE)

re:	fclean $(NAME)

.PHONY: all clean fclean re
