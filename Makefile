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
CFLAGS = 
LIBFT = libft.a
MLX = -lmlx -framework OpenGL -framework AppKit
HEADER = wolf3d.h

OBJECTS = wolf3d.o \
			construct_destruct.o \
			move.o \

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

move.o : move.c $(HEADER)
	$(CC) $(CFLAGS) -c move.c wolf3d.h
