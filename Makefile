# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paperrin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 12:00:36 by paperrin          #+#    #+#              #
#    Updated: 2017/01/09 15:08:12 by paperrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

CC			=	gcc

CFLAGS		=	-g -Wall -Wextra -Werror

RM			=	rm -rf

SRC_DIR		=	./src/

OBJ_DIR		=	./obj/

INC_DIR		=	./include/

CFILES		=	fdf.c			\
				draw_line.c		\
				color.c			\
				map.c			\
				set_pixel.c		\
				event_handler.c

SRC			=	$(CFILES:%=$(SRC_DIR)%)

OBJ			=	$(CFILES:%.c=$(OBJ_DIR)%.o)

# # # # #

all				:	$(NAME)

$(NAME)			:	$(OBJ)
						make -C ./libft/
						$(CC) $(OBJ) -o $@ -L./libft -lft -lmlx \
							-framework OpenGL -framework Appkit

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
						mkdir -p $(OBJ_DIR)
						$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean			:
						$(RM) $(OBJ_DIR)

fclean			:	clean
						$(RM) $(NAME)

re				:	fclean all
