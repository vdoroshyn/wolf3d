/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_destruct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:08:59 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/02 13:39:17 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	construct(t_all *a)
{
	a->win_x = 800;
	a->win_y = 600;
	if (!(a->mlx = mlx_init()))
		exit(0);
	if (!(a->win = mlx_new_window(a->mlx, a->win_x, a->win_y, "window")))
		exit(0);
	a->toggle = 0;
}

void	destruct(t_all *a)
{
	mlx_destroy_window(a->mlx, a->win);
}

void	create_new_image(t_all *a)
{
	a->img = mlx_new_image(a->mlx, a->win_x, a->win_y);
	a->str = mlx_get_data_addr(a->img, &a->bpp, &a->size_line, &a->endian);
}

void	image_to_window_and_destroy(t_all *a)
{
	mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
	mlx_destroy_image(a->mlx, a->img);
}

int		proper_exit(t_all *a)
{
	destruct(a);
	exit(0);
}
