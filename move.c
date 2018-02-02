/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:08:59 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/02 13:39:17 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		move_backwards(t_all *a)
{
	int i;
	int j;

	i = (int)(a->position_x - (a->direction_x * a->ms) * 3);
	j = (int)a->position_y;
	if ((a->map[i][j]) == '0')
	{
		a->position_x -= a->direction_x * a->ms;
	}
	i = (int)a->position_x;
	j = (int)(a->position_y - (a->direction_y * a->ms) * 3);
	if ((a->map[i][j]) == '0')
	{
		a->position_y -= a->direction_y * a->ms;
	}
}

static void		move_forward(t_all *a)
{
	int i;
	int j;

	i = (int)(a->position_x + (a->direction_x * a->ms) * 3);
	j = (int)a->position_y;
	if ((a->map[i][j]) == '0')
	{
		a->position_x += a->direction_x * a->ms;
	}
	i = (int)a->position_x;
	j = (int)(a->position_y + (a->direction_y * a->ms) * 3);
	if ((a->map[i][j]) == '0')
	{
		a->position_y += a->direction_y * a->ms;
	}
}

static void		strafe_left(t_all *a)
{
	int i;
	int j;

	i = (int)(a->position_x - (a->perp_dir_x * a->ms) * 3);
	j = (int)a->position_y;
	if ((a->map[i][j]) == '0')
	{
		a->position_x -= a->perp_dir_x * a->ms;
	}
	i = (int)a->position_x;
	j = (int)(a->position_y - (a->perp_dir_y * a->ms) * 3);
	if ((a->map[i][j]) == '0')
	{
		a->position_y -= a->perp_dir_y * a->ms;
	}
}

static void		strafe_right(t_all *a)
{
	int i;
	int j;

	i = (int)(a->position_x + (a->perp_dir_x * a->ms) * 3);
	j = (int)a->position_y;
	if ((a->map[i][j]) == '0')
	{
		a->position_x += a->perp_dir_x * a->ms;
	}
	i = (int)a->position_x;
	j = (int)(a->position_y + (a->perp_dir_y * a->ms) * 3);
	if ((a->map[i][j]) == '0')
	{
		a->position_y += a->perp_dir_y * a->ms;
	}
}

void			move(t_all *a, int flag)
{
	if (flag == 1)
	{
		move_backwards(a);
	}
	else if (flag == 2)
	{
		move_forward(a);
	}
	else if (flag == 3)
	{
		strafe_left(a);
	}
	else if (flag == 4)
	{
		strafe_right(a);
	}
}
