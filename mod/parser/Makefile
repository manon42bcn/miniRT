
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
				triangle.c
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
				sphere.c
SRCS_DIR	=	srcs
OBJS_DIR	=	obj
BNS_DIR		=	bns
OBJS_B_DIR	=	obj_bns
OBJS 		=	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
OBJS_BNS 	=	$(addprefix $(OBJS_B_DIR)/,$(SRCS_B:.c=.o))
OBJS_SUBS	= 	obj
CC			=	gcc
RM			=	@rm -rf
CFLAGS 		=	-Wall -Wextra -Werror -Iinc -I../inc
NAME		=	libparser.a
HEADER		=	inc/parse.h \
				inc/parse_enum.h \
				../../inc/objects.h \
				../../inc/structs.h
BONUS_FILE	= .bonus

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
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJS_DIR):
	-@mkdir $(OBJS_DIR)

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
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJS_B_DIR):
	-@mkdir $(OBJS_B_DIR)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_DIR) $(OBJS_B_DIR)
	$(RM) $(BONUS_FILE)

re:	fclean $(NAME)

.PHONY: all clean fclean re
