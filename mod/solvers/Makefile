
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

SRCS_B		=	cube.c \
				pyramid.c \
				square.c \
				triangle.c \
				cone.c \
				hyperboloid.c \
				paraboloid.c \
				ellipsoid.c
SRCS		=	cylinder.c \
				cylinder_tops.c \
				plane.c \
				solvers.c \
				sphere.c
SRCS_DIR	=	srcs
OBJS_DIR	=	obj
BNS_DIR		=	bns
OBJS_B_DIR	=	obj_bns
OBJS 		=	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
OBJS_BNS 	=	$(addprefix $(OBJS_B_DIR)/,$(SRCS_B:.c=.o))
CC			=	gcc
RM			=	@rm -rf
NAME		=	libsolvers.a
HEADER		=	inc/solvers.h \
				../../libs/v3d/inc/v3d.h \
                ../../libs/rgb/inc/rgb.h \
                ../../libs/lib/inc/libft.h \
				../../inc/defines.h \
				../../inc/objects.h \
                ../../inc/structs.h
CFLAGS 		=	-Wall -Wextra -Werror
INCLUDES	:=	$(patsubst %,-I%,$(dir $(HEADER)))
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
	$(RM) $(BONUS_FILE)

bonus: CFLAGS += -DBONUS
bonus: version_bonus $(BONUS_FILE)

version_bonus:
	@if [ ! -f $(BONUS_FILE) ] && [ -f $(NAME) ]; then \
		$(MAKE) fclean; \
    fi

$(BONUS_FILE): $(OBJS_DIR) $(OBJS_B_DIR) $(OBJS) $(OBJS_BNS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BNS)
	touch $(BONUS_FILE)

$(OBJS_B_DIR)/%.o: $(BNS_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

$(OBJS_B_DIR):
	-@mkdir $(OBJS_B_DIR)

re:	fclean $(NAME)

.PHONY: all clean fclean re bonus
