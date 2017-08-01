# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paperrin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 12:00:36 by paperrin          #+#    #+#              #
#    Updated: 2017/08/01 21:18:51 by paperrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

CC			=	gcc

CFLAGS		=	-g -Wall -Wextra -Werror

RM			=	rm -rf

SRC_DIR		=	./src/

OBJ_DIR		=	./obj/

INC_DIRS	=	./include/		\
				./mlx/include/	\

LIB_DIRS	=	./libft/		\
				./mlx/

LIBS		=	-lft			\
				-lmlx

INC_PARAMS	=	$(INC_DIRS:%=-I%)

LIB_PARAMS	=	$(LIB_DIRS:%=-L%)

CFILES		=	fdf.c				\
				draw_line.c			\
				color.c				\
				map.c				\
				render.c			\
				set_pixel.c			\
				clear_image.c		\
				update_matrices.c	\
				event_handler.c

HFILES		=	./include/fdf.h

SRC			=	$(CFILES:%=$(SRC_DIR)%)

OBJ			=	$(CFILES:%.c=$(OBJ_DIR)%.o)

# # # # #

all				:	$(NAME)

$(NAME)			:	$(OBJ) $(HFILES)
						make -C ./mlx/
						make -C ./libft/
						$(CC) $(OBJ) -o $@ $(LIB_PARAMS) $(LIBS) \
							-framework OpenGL -framework Appkit

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
						mkdir -p $(OBJ_DIR)
						$(CC) $(CFLAGS) $(INC_PARAMS) -c $< -o $@

clean			:
						$(RM) $(OBJ_DIR)
						make -C ./mlx/ clean
						make -C ./libft/ clean


fclean			:	clean
						$(RM) $(NAME)
						make -C ./libft/ fclean

re				:	fclean all

norm			:
	@echo "\x1b[35m\n.==================[ \x1b[0m\c"
	@echo "\x1b[35;1mNormi-Check\x1b[0m\c"
	@echo " \x1b[35m]==================.\x1b[31;1m"
	@norminette include/ src/ \
		| tr "\n" "@" \
		| sed -e "s/Norme: /$$/g" \
		| tr "$$" "\n" \
		| grep -e Error -e Warning \
		| tr "@" "\n" \
		| sed "N;$$!P;$$!D;$$d"
	@echo "\x1b[0m\x1b[35m\c"
	@echo ".___________________________________________________.\n\x1b[0m"

.PHONY : all, clean, fclean, re, norm
