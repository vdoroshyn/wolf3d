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

static int		is_not_wall(char c)
{
	if (c == '0' || c == 'P')
	{
		return (1);
	}
	return (0);
}

static int		is_border_valid(char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_not_wall(str[i]))
		{
			return (0);
		}
		++i;
	}
	return (1);
}

static int		are_top_bottom_borders_valid(t_all *a)
{
	if (!is_border_valid(a->map[0]) || !is_border_valid(a->map[a->map_y - 1]))
	{
		return (0);
	}
	return (1);
}

static int		are_right_left_borders_valid(t_all *a)
{
	int			i;

	i = 0;
	while (i < a->map_y)
	{
		if (is_not_wall(a->map[i][0]) || is_not_wall(a->map[i][a->map_x - 1]))
		{
			return (0);
		}
		++i;
	}
	return (1);
}

int				are_all_map_borders_valid(t_all *a)
{
	if (!are_right_left_borders_valid(a) || !are_top_bottom_borders_valid(a))
	{
		return (0);
	}
	return (1);
}
