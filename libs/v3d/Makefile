
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
	@ar rcs $(NAME) $(OBJS)
	@echo "$(MAGENTA)Library $@ compiled$(DEF_COLOR)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)$(patsubst $(SRCS_DIR)/%,%, $<)" | awk '{printf "%-50s\tcompiled ✓$(DEF_COLOR)\n", $$0;}'
	

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
