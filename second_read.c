/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 13:54:33 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/04 13:54:42 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**open the fd first time
**read line by line comparing their size
**check whether each node consists of numbers only or letter P
**check whether there is one and only one letter P on the map

**open the fd second time
**atoi every coord and put them into malloced map_x x map_y array
**check whether borders consist not of 0 (sides: check size first, then compare the first and last symbols)
**init player position in the struct and put 0 in the array
*/

static void		null_pointer_map_array(t_all *a)
{
	int			i;

	i = 0;
	while (i <= a->map_y)
	{
		a->map[i] = NULL;
		++i;
	}
}

void			create_pointer_map_array(t_all *a)
{
	a->map = (char **)malloc(sizeof(char *) * (a->map_y + 1));
	if (a->map == NULL)
	{
		exit(5);
	}
	null_pointer_map_array(a);	
}

static void			initialize_player_position(t_all *a)
{
	int			i;
	int			j;

	i = 0;
	while (i < a->map_y)
	{
		j = 0;
		while (j < a->map_x)
		{
			if (is_player(a->map[i][j]))
			{
				a->map[i][j] = '0';
				a->posX = i + 0.5;
				a->posY = j + 0.5;
				return ;
			}
			++j;
		}
		++i;
	}
}

void		free_map(t_all *a)
{
	int			i;

	i = 0;
	while (a->map[i] != NULL)
	{
		free(a->map[i]);
		a->map[i] = NULL;
		++i;
	}
	free(a->map);
	a->map = NULL;
}

void			read_file_2(char *str, t_all *a)
{
	int			fd;
	int			i;
	char		*line;

	i = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("There was an error with the file descriptor");
		exit(6);
	}
	i = 0;
	while (i < a->map_y)
	{	
		if (get_next_line(fd, &line) == -1)
		{
			free_map(a);
			exit(7);
		}
		a->map[i] = line;
		++i;
	}
	if (!are_all_map_borders_valid(a))
	{
		free_2d_array((void **)a->map, a->map_y);
		write(2, "the map is not valid\n", 21);
		exit(8);
	}
	initialize_player_position(a);
	close(fd);
}
