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

static void		draw_one_minimap_square(t_all *a, int pixel, t_color color)
{
	color_one_pixel(a, pixel, color);
	color_one_pixel(a, pixel + 4, color);
	color_one_pixel(a, pixel + a->size_line, color);
	color_one_pixel(a, pixel + a->size_line + 4, color);
}

static void		draw_player_on_minimap(t_all *a)
{
	int			player_x;
	int			player_y;
	int			pixel;
	t_color		color;

	player_x = (int)a->position_x;
	player_y = (int)a->position_y;
	pixel = 4 * player_y * 4 + 4 * player_x * a->size_line;
	color.transp = 0;
	color.red = 0;
	color.green = 255;
	color.blue = 0;
	draw_one_minimap_square(a, pixel, color);
}

void			draw_minimap(t_all *a)
{
	int			i;
	int			j;
	int			pixel;
	t_color		color;

	color.transp = 0;
	color.red = 255;
	color.green = 255;
	color.blue = 255;
	i = 0;
	while (i < a->map_h)
	{
		j = 0;
		while (j < a->map_w)
		{
			pixel = 4 * j * 4 + 4 * i * a->size_line;
			if (a->map[i][j] != '0')
			{
				draw_one_minimap_square(a, pixel, color);
			}
			++j;
		}
		++i;
	}
	draw_player_on_minimap(a);
}
