/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation1.c                                      :+:      :+:    :+:   */
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
**check whether each node consists of numbers only or letter P (no more than 9 symbols)
**check whether there is one and only one letter P on the map

**open the fd second time
**atoi every coord and put them into malloced map_x x map_y array
**check whether borders consist not of 0 (sides: check size first, then compare the first and last symbols)
**init player position in the struct and put 0 in the array
*/

static int		is_player(char c, int *player_count)
{
	if (c != 'P')
	{
		return (0);
	}
	return (1);
}

static int		ft_validate(char *line, int *player_count)
{
	int			i;
	int			number_of_symbols;

	i = 0;
	number_of_symbols = 0;
	while (line[i] != '\0')
	{
		if (is_player(line[i]))
		{
			*player_count += 1;
		}
		else if (!ft_isdigit(line[i]))
		{
			return (0);
		}
		++number_of_symbols;
		++i;
	}
	return (number_of_symbols);
}

static int		gnl_validate(int fd, int *player_count, t_all *a)
{
	int			check;
	int			count;
	char		*line;

	check = 0;
	while (get_next_line(fd, &line) > 0)
	{
		check = 1;
		a->map_y += 1;
		count = ft_validate(line, player_count);
		if (a->map_x == 0)
		{
			a->map_x = count;
		}
		if (a->map_x != count)
		{
			write(2, "the map is not valid\n", 21);
			free(line);
			close(fd);
			exit(3);
		}
		ft_strdel(&line);
	}
	return (check);
}

void			get_map_size(char *str, t_all *a)
{
	int			check;
	int			fd;
	int			player_count;

	a->map_x = 0;
	a->map_y = 0;
	player_count = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("There was an error with the file descriptor");
		exit(1);
	}
	check = gnl_validate(fd, &player_count, a);
	if (check == 0)
	{
		perror("There is nothing in the file");
		close(fd);
		exit(2);
	}
	close(fd);
}
