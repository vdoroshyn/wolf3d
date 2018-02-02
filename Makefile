#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/02 16:51:50 by vdoroshy          #+#    #+#              #
#    Updated: 2017/03/02 16:51:57 by vdoroshy         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a
MLX = -lmlx -framework OpenGL -framework AppKit
HEADER = wolf3d.h

OBJECTS = wolf3d.o \
			construct_destruct.o \
			move.o \
			rotate.o \
			load_window.o \
			load_textures.o \
			first_read.o \
			second_read.o \
			map_borders.o \
			draw_textures.o \
			draw_minimap.o \
			draw_walls.o \
			draw_floor_ceiling.o \
			controls.o \

.PHONY : clean all fclean re

all : $(LIBFT) $(NAME)
	
$(NAME) : $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(MLX) libft/$(LIBFT)

$(LIBFT) :
	make -C libft/

clean :
	rm -rf $(OBJECTS)
	make -C libft/ clean

fclean : clean
	rm -rf $(NAME)
	rm -rf libft/$(LIBFT)

re : fclean all

wolf3d.o : wolf3d.c $(HEADER)
	$(CC) $(CFLAGS) -c wolf3d.c wolf3d.h

construct_destruct.o : construct_destruct.c $(HEADER)
	$(CC) $(CFLAGS) -c construct_destruct.c wolf3d.h

draw_textures.o : draw_textures.c $(HEADER)
	$(CC) $(CFLAGS) -c draw_textures.c wolf3d.h

draw_minimap.o : draw_minimap.c $(HEADER)
	$(CC) $(CFLAGS) -c draw_minimap.c wolf3d.h

draw_walls.o : draw_walls.c $(HEADER)
	$(CC) $(CFLAGS) -c draw_walls.c wolf3d.h

draw_floor_ceiling.o : draw_floor_ceiling.c $(HEADER)
	$(CC) $(CFLAGS) -c draw_floor_ceiling.c wolf3d.h

first_read.o : first_read.c $(HEADER)
	$(CC) $(CFLAGS) -c first_read.c wolf3d.h

second_read.o : second_read.c $(HEADER)
	$(CC) $(CFLAGS) -c second_read.c wolf3d.h

map_borders.o : map_borders.c $(HEADER)
	$(CC) $(CFLAGS) -c map_borders.c wolf3d.h

move.o : move.c $(HEADER)
	$(CC) $(CFLAGS) -c move.c wolf3d.h

rotate.o : rotate.c $(HEADER)
	$(CC) $(CFLAGS) -c rotate.c wolf3d.h

load_window.o : load_window.c $(HEADER)
	$(CC) $(CFLAGS) -c load_window.c wolf3d.h

load_textures.o : load_textures.c $(HEADER)
	$(CC) $(CFLAGS) -c load_textures.c wolf3d.h

controls.o : controls.c $(HEADER)
	$(CC) $(CFLAGS) -c controls.c wolf3d.h