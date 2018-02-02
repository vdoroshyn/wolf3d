/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:03:15 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/09 16:03:27 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_floor(t_all *a, int y, int x)
{
	int			pixel;

	pixel = x * 4 + y * a->size_line;
	a->col.transp = 0;
	a->col.red = a->purplestone[(64 * a->floor_tex_y
		+ a->floor_tex_x) * 4 + 2];
	a->col.green = a->purplestone[((64 * a->floor_tex_y
		+ a->floor_tex_x) * 4) + 1];
	a->col.blue = a->purplestone[((64 * a->floor_tex_y
		+ a->floor_tex_x) * 4) + 0];
	color_one_pixel(a, pixel);
}

static void		draw_ceiling(t_all *a, int y, int x)
{
	int pixel;

	pixel = x * 4 + (a->win_y - y) * a->size_line;
	a->col.transp = 0;
	a->col.red = a->redbrick[(64 * a->floor_tex_y
		+ a->floor_tex_x) * 4 + 2];
	a->col.green = a->redbrick[((64 * a->floor_tex_y
		+ a->floor_tex_x) * 4) + 1];
	a->col.blue = a->redbrick[((64 * a->floor_tex_y
		+ a->floor_tex_x) * 4) + 0];
	color_one_pixel(a, pixel);
}

void			draw_floor_and_ceiling(t_all *a, int x)
{
	int			y;

	y = a->draw_end + 1;
	while (y < a->win_y)
	{
		a->current_dist = a->win_y / (2.0 * y - a->win_y);
		a->weight = (a->current_dist - a->dist_to_player)
		/ (a->dist_to_wall - a->dist_to_player);
		a->current_floor_x = a->weight * a->floor_x_wall
		+ (1.0 - a->weight) * a->position_x;
		a->current_floor_y = a->weight * a->floor_y_wall
		+ (1.0 - a->weight) * a->position_y;
		a->floor_tex_x = (int)(a->current_floor_x * 64) % 64;
		a->floor_tex_y = (int)(a->current_floor_y * 64) % 64;
		draw_floor(a, y, x);
		draw_ceiling(a, y, x);
		++y;
	}
}
