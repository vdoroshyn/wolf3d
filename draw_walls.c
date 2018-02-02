/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:03:15 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/09 16:03:27 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_north_south_walls(t_all *a)
{
	if (a->x_step > 0)
	{
		a->col.transp = 0;
		a->col.red = (unsigned char)(a->wd[(64 * a->tex_y
			+ a->tex_x) * 4 + 2]) / 2;
		a->col.green = (unsigned char)(a->wd[((64 * a->tex_y
			+ a->tex_x) * 4) + 1]) / 2;
		a->col.blue = (unsigned char)(a->wd[((64 * a->tex_y
			+ a->tex_x) * 4) + 0]) / 2;
	}
	else
	{
		a->col.transp = 0;
		a->col.red = a->m[(64 * a->tex_y + a->tex_x) * 4 + 2];
		a->col.green = a->m[((64 * a->tex_y + a->tex_x) * 4) + 1];
		a->col.blue = a->m[((64 * a->tex_y + a->tex_x) * 4) + 0];
	}
}

static void		draw_east_west_walls(t_all *a)
{
	if (a->y_step > 0)
	{
		a->col.transp = 0;
		a->col.red = a->gs[(64 * a->tex_y + a->tex_x) * 4 + 2];
		a->col.green = a->gs[((64 * a->tex_y + a->tex_x) * 4) + 1];
		a->col.blue = a->gs[((64 * a->tex_y + a->tex_x) * 4) + 0];
	}
	else
	{
		a->col.transp = 0;
		a->col.red = a->cs[(64 * a->tex_y + a->tex_x) * 4 + 2];
		a->col.green = a->cs[((64 * a->tex_y + a->tex_x) * 4) + 1];
		a->col.blue = a->cs[((64 * a->tex_y + a->tex_x) * 4) + 0];
	}
}

void			draw_walls(t_all *a, int x)
{
	int			pixel;
	int			y;

	y = a->draw_start;
	while (y < a->draw_end)
	{
		pixel = x * 4 + y * a->size_line;
		a->avoid_floats = y * 256 - a->win_y * 128 + a->line_h * 128;
		a->tex_y = ((a->avoid_floats * 64) / a->line_h) / 256;
		if (a->side == 0)
		{
			draw_north_south_walls(a);
		}
		else
		{
			draw_east_west_walls(a);
		}
		color_one_pixel(a, pixel);
		++y;
	}
}
