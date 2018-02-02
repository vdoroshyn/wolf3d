/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 13:54:33 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/04 13:54:42 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_one_minimap_square(t_all *a, int pixel)
{
	color_one_pixel(a, pixel);
	color_one_pixel(a, pixel + 4);
	color_one_pixel(a, pixel + a->size_line);
	color_one_pixel(a, pixel + a->size_line + 4);
}

static void		draw_player_on_minimap(t_all *a)
{
	int			player_x;
	int			player_y;
	int			pixel;

	player_x = (int)a->position_x;
	player_y = (int)a->position_y;
	pixel = 4 * player_y * 4 + 4 * player_x * a->size_line;
	a->col.transp = 0;
	a->col.red = 0;
	a->col.green = 255;
	a->col.blue = 0;
	draw_one_minimap_square(a, pixel);
}

void			draw_minimap(t_all *a)
{
	int			i;
	int			j;
	int			pixel;

	a->col.transp = 0;
	a->col.red = 255;
	a->col.green = 255;
	a->col.blue = 255;
	i = 0;
	while (i < a->map_h)
	{
		j = 0;
		while (j < a->map_w)
		{
			pixel = 4 * j * 4 + 4 * i * a->size_line;
			if (a->map[i][j] != '0')
			{
				draw_one_minimap_square(a, pixel);
			}
			++j;
		}
		++i;
	}
	draw_player_on_minimap(a);
}
