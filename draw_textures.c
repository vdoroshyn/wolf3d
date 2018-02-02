/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:03:15 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/09 16:03:27 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			color_one_pixel(t_all *a, int pixel)
{
	a->str[pixel] = a->col.blue;
	a->str[pixel + 1] = a->col.green;
	a->str[pixel + 2] = a->col.red;
	a->str[pixel + 3] = a->col.transp;
}

static void		calculate_draw_start_and_end(t_all *a)
{
	a->line_h = (int)(a->win_y / a->perp_wall_dist);
	a->draw_start = -a->line_h / 2 + a->win_y / 2;
	if (a->draw_start < 0)
	{
		a->draw_start = 0;
	}
	a->draw_end = a->line_h / 2 + a->win_y / 2;
	if (a->draw_end >= a->win_y)
	{
		a->draw_end = a->win_y - 1;
	}
}

static void		floor_and_ceiling_calculations(t_all *a)
{
	if (a->side == 0 && a->ray_direction_x > 0)
	{
		a->floor_x_wall = a->map_x;
		a->floor_y_wall = a->map_y + a->wall_x;
	}
	else if (a->side == 0 && a->ray_direction_x < 0)
	{
		a->floor_x_wall = a->map_x + 1.0;
		a->floor_y_wall = a->map_y + a->wall_x;
	}
	else if (a->side == 1 && a->ray_direction_y > 0)
	{
		a->floor_x_wall = a->map_x + a->wall_x;
		a->floor_y_wall = a->map_y;
	}
	else
	{
		a->floor_x_wall = a->map_x + a->wall_x;
		a->floor_y_wall = a->map_y + 1.0;
	}
	a->dist_to_wall = a->perp_wall_dist;
	a->dist_to_player = 0.0;
	if (a->draw_end < 0)
		a->draw_end = a->win_y;
}

void			draw(t_all *a, int x)
{
	calculate_draw_start_and_end(a);
	draw_walls(a, x);
	floor_and_ceiling_calculations(a);
	draw_floor_and_ceiling(a, x);
}
