/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:05:44 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/16 14:28:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			ray_position_and_direction_calculations(t_all *a, int x)
{
	a->camera_x = 2 * x / (double)a->win_x - 1;
	a->ray_position_x = a->position_x;
	a->ray_position_y = a->position_y;
	a->ray_direction_x = a->direction_x + a->perp_dir_x * a->camera_x;
	a->ray_direction_y = a->direction_y + a->perp_dir_y * a->camera_x;
	a->map_x = (int)a->ray_position_x;
	a->map_y = (int)a->ray_position_y;
	a->delta_dist_x = sqrt(1 + (a->ray_direction_y * a->ray_direction_y)
		/ (a->ray_direction_x * a->ray_direction_x));
	a->delta_dist_y = sqrt(1 + (a->ray_direction_x * a->ray_direction_x)
		/ (a->ray_direction_y * a->ray_direction_y));
	a->hit = 0;
}

static void			side_dist_step_calculations(t_all *a)
{
	if (a->ray_direction_x < 0)
	{
		a->side_dist_x = (a->ray_position_x - a->map_x) * a->delta_dist_x;
		a->x_step = -1;
	}
	else
	{
		a->side_dist_x = (a->map_x + 1.0 - a->ray_position_x) * a->delta_dist_x;
		a->x_step = 1;
	}
	if (a->ray_direction_y < 0)
	{
		a->side_dist_y = (a->ray_position_y - a->map_y) * a->delta_dist_y;
		a->y_step = -1;
	}
	else
	{
		a->side_dist_y = (a->map_y + 1.0 - a->ray_position_y) * a->delta_dist_y;
		a->y_step = 1;
	}
}

static void			dda_wall_collision(t_all *a)
{
	while (a->hit == 0)
	{
		if (a->side_dist_x < a->side_dist_y)
		{
			a->side_dist_x += a->delta_dist_x;
			a->map_x += a->x_step;
			a->side = 0;
		}
		else
		{
			a->side_dist_y += a->delta_dist_y;
			a->map_y += a->y_step;
			a->side = 1;
		}
		if (a->map[a->map_x][a->map_y] > '0')
		{
			a->hit = 1;
		}
	}
}

static void			distance_wallx_calculations(t_all *a)
{
	if (a->side == 0)
	{
		a->perp_wall_dist = (a->map_x - a->ray_position_x
			+ (1 - a->x_step) / 2) / a->ray_direction_x;
	}
	else
	{
		a->perp_wall_dist = (a->map_y - a->ray_position_y
			+ (1 - a->y_step) / 2) / a->ray_direction_y;
	}
	if (a->side == 0)
	{
		a->wall_x = a->ray_position_y + a->perp_wall_dist * a->ray_direction_y;
	}
	else
	{
		a->wall_x = a->ray_position_x + a->perp_wall_dist * a->ray_direction_x;
	}
	a->wall_x -= floor((a->wall_x));
}

void				load_window(t_all *a)
{
	int x;

	create_new_image(a);
	x = 0;
	while (x < a->win_x)
	{
		ray_position_and_direction_calculations(a, x);
		side_dist_step_calculations(a);
		dda_wall_collision(a);
		distance_wallx_calculations(a);
		a->tex_x = (int)(a->wall_x * (double)64);
		if (a->side == 0 && a->ray_direction_x > 0)
		{
			a->tex_x = 64 - a->tex_x - 1;
		}
		if (a->side == 1 && a->ray_direction_y < 0)
		{
			a->tex_x = 64 - a->tex_x - 1;
		}
		draw(a, x);
		++x;
	}
	draw_minimap(a);
	image_to_window_and_destroy(a);
	load_gun(a);
}
