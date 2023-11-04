
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

SRCS		=	camera_handlers.c \
				camera_translate_handlers.c \
				keys_handlers.c \
				light_handlers.c \
				modes_handlers.c \
				normal_handlers.c \
				objects_handlers.c \
				selection_handlers.c \
				special_handlers.c
SRCS_DIR	=	src
OBJS_DIR	=	obj
OBJS 		=	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
CC			=	gcc
RM			=	@rm -rf
NAME		=	libhooks.a
HEADER		=	inc/hooks.h \
				../../libs/v3d/inc/v3d.h \
				../../libs/rgb/inc/rgb.h \
				../../libs/lib/inc/libft.h \
				../../common/defines.h \
				../../common/objects.h \
                ../../common/structs.h \
				../parser/inc/parse.h

CFLAGS 		=	-Wall -Wextra -Werror
INCLUDES	= -Iinc -I../../libs/v3d/inc -I../../libs/rgb/inc -I../../libs/lib/inc -I../parser/inc -I../../inc -I../../common

all: $(NAME) $(HEADER)

$(NAME): $(OBJS_DIR) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
