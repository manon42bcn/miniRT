
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
	@ar rcs $(NAME) $(OBJS)
	@echo "$(MAGENTA)Library $@ compiled$(DEF_COLOR)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@
	@echo "$(GREEN)$(patsubst $(SRCS_DIR)/%,%, $<)" | awk '{printf "%-50s\tcompiled ✓$(DEF_COLOR)\n", $$0;}'

$(OBJS_DIR):
	-@mkdir $(OBJS_DIR)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_SUBS)
	$(RM) $(BONUS_FILES)

bonus: CFLAGS += -DBONUS
bonus: version_bonus $(BONUS_FILE) $(HEADER)

version_bonus:
	@if [ ! -f $(BONUS_FILE) ] && [ -f $(NAME) ]; then \
		$(MAKE) fclean; \
    fi

$(BONUS_FILE): $(OBJS_DIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS) $(OBJS_BNS)
	@touch $(BONUS_FILE)
	@echo "$(MAGENTA)Library $@ compiled$(DEF_COLOR)"

re:	fclean $(NAME)

.PHONY: all clean fclean re bonus
