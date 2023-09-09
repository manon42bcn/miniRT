
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

SRCS		=	camera_hooks.c \
				camera_orbit_hooks.c \
				common.c \
				cylinder_hooks.c \
				cylinder_rotation_hooks.c \
				keys_handler.c \
				light_rotation_hooks.c \
				main_hooks.c \
				mouse_handler.c \
				sphere_hooks.c
SRCS_DIR	=	src
OBJS_DIR	=	obj
OBJS 		=	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
CC			=	gcc
RM			=	@rm -rf
CFLAGS 		=	-Wall -Wextra -Werror -Iinc
NAME		=	libhooks.a
HEADER		=	inc/hooks.h \
				../parser/inc/parse.h \
				../../inc/objects.h \
                ../../inc/structs.h

all: $(NAME) $(HEADER)

$(NAME): $(OBJS_DIR) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	-@mkdir $(OBJS_DIR)

bonus: CFLAGS += -DBONUS
bonus: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_DIR)

re:	fclean $(NAME)

.PHONY: all clean fclean re
