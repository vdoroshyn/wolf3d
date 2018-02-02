/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:05:44 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/16 14:28:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		turn_left(t_all *a)
{
	double old_dir_x;
	double old_perp_dir_x;

	old_dir_x = a->direction_x;
	a->direction_x = a->direction_x * cos(a->rotation_speed)
		- a->direction_y * sin(a->rotation_speed);
	a->direction_y = old_dir_x * sin(a->rotation_speed)
		+ a->direction_y * cos(a->rotation_speed);
	old_perp_dir_x = a->perp_dir_x;
	a->perp_dir_x = a->perp_dir_x * cos(a->rotation_speed)
		- a->perp_dir_y * sin(a->rotation_speed);
	a->perp_dir_y = old_perp_dir_x * sin(a->rotation_speed)
		+ a->perp_dir_y * cos(a->rotation_speed);
}

static void		turn_right(t_all *a)
{
	double old_dir_x;
	double old_perp_dir_x;

	old_dir_x = a->direction_x;
	a->direction_x = a->direction_x * cos(-a->rotation_speed)
		- a->direction_y * sin(-a->rotation_speed);
	a->direction_y = old_dir_x * sin(-a->rotation_speed)
		+ a->direction_y * cos(-a->rotation_speed);
	old_perp_dir_x = a->perp_dir_x;
	a->perp_dir_x = a->perp_dir_x * cos(-a->rotation_speed)
		- a->perp_dir_y * sin(-a->rotation_speed);
	a->perp_dir_y = old_perp_dir_x * sin(-a->rotation_speed)
		+ a->perp_dir_y * cos(-a->rotation_speed);
}

void			rotate(t_all *a, int flag)
{
	if (flag == 1)
	{
		turn_left(a);
	}
	else if (flag == 2)
	{
		turn_right(a);
	}
}
