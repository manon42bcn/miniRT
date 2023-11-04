
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

SRCS		=	cylinder.c \
				cylinder_tops.c \
				plane.c \
				solvers.c \
				sphere.c \
				quadratic.c \
				normals.c \
				box.c \
                triangle.c \
                cone.c \
                ellipsoid.c \
                rectangle.c
SRCS_DIR	=	srcs
OBJS_DIR	=	obj
OBJS 		=	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
CC			=	gcc
RM			=	@rm -rf
NAME		=	libsolvers.a
HEADER		=	inc/solvers.h \
				../../libs/v3d/inc/v3d.h \
                ../../libs/rgb/inc/rgb.h \
                ../../libs/lib/inc/libft.h \
				../../common/defines.h \
				../../common/objects.h \
                ../../common/structs.h
CFLAGS 		=	-Wall -Wextra -Werror
INCLUDES 	= 	-Iinc -I../../libs/v3d/inc -I../../libs/rgb/inc -I../../libs/lib/inc -I../parser/inc -I../../inc -I../../common
BONUS_FILE	= 	.bonus

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

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_SUBS)

bonus: CFLAGS += -DBONUS
bonus: version_bonus $(BONUS_FILE) $(HEADER)

version_bonus:
	@if [ ! -f $(BONUS_FILE) ] && [ -f $(NAME) ]; then \
		$(MAKE) fclean; \
    fi

$(BONUS_FILE): $(OBJS_DIR) $(OBJS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BNS)
	touch $(BONUS_FILE)

re:	fclean $(NAME)

.PHONY: all clean fclean re bonus
