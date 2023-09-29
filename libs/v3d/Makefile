
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

SRCS		=	v3d_algebra.c \
				v3d_arithmetics.c \
				v3d_extra.c \
				v3d_utils.c \
				v3d_tools.c
SRCS_DIR	=	src
OBJS 		=	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
OBJS_SUBS	= 	obj
CC			=	gcc
RM			=	@rm -rf
CFLAGS 		=	-Wall -Wextra -Werror -Iinc
NAME		=	libv3d.a
HEADER		=	inc/v3d.h
OBJS_DIR	=	obj

all: $(NAME) $(HEADER)

$(NAME): $(OBJS_SUBS) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_SUBS):
	-@mkdir $(OBJS_SUBS)

bonus: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_SUBS)

re:	fclean $(NAME)

.PHONY: all clean fclean re
