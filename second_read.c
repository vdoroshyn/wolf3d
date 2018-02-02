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

static void		null_pointer_map_array(t_all *a)
{
	int			i;

	i = 0;
	while (i <= a->map_h)
	{
		a->map[i] = NULL;
		++i;
	}
}

void			create_pointer_map_array(t_all *a)
{
	a->map = (char **)malloc(sizeof(char *) * (a->map_h + 1));
	if (a->map == NULL)
	{
		exit(5);
	}
	null_pointer_map_array(a);
}

static void		borders_error(t_all *a)
{
	if (!are_all_map_borders_valid(a))
	{
		free_2d_array((void **)a->map, a->map_h);
		write(2, "the map is not valid\n", 21);
		exit(8);
	}
}

static void		initialize_player_position(t_all *a)
{
	int			i;
	int			j;

	i = 0;
	while (i < a->map_h)
	{
		j = 0;
		while (j < a->map_w)
		{
			if (is_player(a->map[i][j]))
			{
				a->map[i][j] = '0';
				a->position_x = i + 0.5;
				a->position_y = j + 0.5;
				return ;
			}
			++j;
		}
		++i;
	}
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
	while (i < a->map_h)
	{
		if (get_next_line(fd, &line) == -1)
		{
			free_map(a);
			exit(7);
		}
		a->map[i] = line;
		++i;
	}
	borders_error(a);
	initialize_player_position(a);
	close(fd);
}
