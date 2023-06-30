
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

SRCS		=	cube.c \
				cylinder.c \
				parser_ambient.c \
				parser_builders.c \
				parser_camera.c \
				parser_errors.c \
				parser_light.c \
				parser_resolution.c \
				parser_rgb.c \
				parser_utils.c \
				parser_v3d.c \
				plane.c \
				pyramid.c \
				readfile.c \
				sphere.c \
				square.c \
				triangle.c
SRCS_DIR	=	srcs
OBJS 		=	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
OBJS_SUBS	= 	obj
CC			=	gcc
RM			=	@rm -rf
CFLAGS 		=	-Wall -Wextra -Werror -Iinc
NAME		=	libparser.a
HEADER		=	inc/parse.h \
				inc/objects.h \
				inc/parse_enum.h \
				inc/structs.h
OBJS_DIR	=	obj

all: $(NAME) $(HEADER)

$(NAME): $(OBJS_SUBS) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	$(CC) -Iinc $(CFLAGS) -g -c $< -o $@

$(OBJS_SUBS):
	-@mkdir $(OBJS_SUBS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_SUBS)

re:	fclean $(NAME)

.PHONY: all clean fclean re
