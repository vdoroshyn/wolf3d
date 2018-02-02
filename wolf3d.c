/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:05:44 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/16 14:28:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		calculate_ms_and_rs(t_all *a)
{
	a->old_time = a->time;
	a->time = clock();
	a->delta_time = (a->time - a->old_time) / 1000.0;
	a->ms = a->delta_time * 5.0;
	a->rotation_speed = a->delta_time * 0.001;
}

int				main(int argc, char **argv)
{
	t_all		a;

	a.map = NULL;
	a.win_x = 800;
	a.win_y = 600;
	if (argc != 2)
	{
		write(1, "usage: ./wolf3d file_with_map\n", 30);
		exit(1);
	}
	read_file_1(argv[1], &a);
	create_pointer_map_array(&a);
	read_file_2(argv[1], &a);
	construct(&a);
	load_window(&a);
	calculate_ms_and_rs(&a);
	mlx_hook(a.win, 2, 1, key_press, &a);
	mlx_hook(a.win, 3, 2, key_release, &a);
	mlx_hook(a.win, 17, 1L << 17, proper_exit, &a);
	mlx_loop_hook(a.mlx, reload_window, &a);
	mlx_loop(a.mlx);
}
