/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 13:54:33 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/04 13:54:42 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				is_player(char c)
{
	if (c != 'P')
	{
		return (0);
	}
	return (1);
}

static int		count_line_symbols(char *line, int *player_count)
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

static int		get_map_size(int fd, int *player_count, t_all *a)
{
	int			is_file_empty;
	int			number_of_symbols;
	char		*line;

	is_file_empty = 1;
	while (get_next_line(fd, &line) > 0)
	{
		is_file_empty = 0;
		a->map_h += 1;
		number_of_symbols = count_line_symbols(line, player_count);
		if (a->map_w == 0)
		{
			a->map_w = number_of_symbols;
		}
		if (a->map_w != number_of_symbols || a->map_w < 5 || a->map_w > 50)
		{
			write(2, "the map is not valid\n", 21);
			ft_strdel(&line);
			close(fd);
			exit(4);
		}
		ft_strdel(&line);
	}
	return (is_file_empty);
}

void			read_file_1(char *str, t_all *a)
{
	int			is_file_empty;
	int			fd;
	int			player_count;

	a->map_w = 0;
	a->map_h = 0;
	player_count = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("There was an error with the file descriptor");
		exit(2);
	}
	is_file_empty = get_map_size(fd, &player_count, a);
	if (is_file_empty || a->map_h < 5 || a->map_h > 50 || player_count != 1)
	{
		write(2, "the map is not valid\n", 21);
		close(fd);
		exit(3);
	}
	close(fd);
}
