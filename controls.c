/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:05:44 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/16 14:28:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_press(int keycode, t_all *a)
{
	if (keycode == 53)
		proper_exit(a);
	else if (keycode == 1)
		a->is_moving = 1;
	else if (keycode == 13)
		a->is_moving = 2;
	else if (keycode == 12)
		a->is_moving = 3;
	else if (keycode == 14)
		a->is_moving = 4;
	else if (keycode == 0)
		a->is_rotating = 1;
	else if (keycode == 2)
		a->is_rotating = 2;
	else if (keycode == 257)
		a->is_sprinting = 1;
	reload_window(a);
	return (0);
}

int		key_release(int keycode, t_all *a)
{
	if (keycode == 1 || keycode == 13 || keycode == 12 || keycode == 14)
		a->is_moving = 0;
	else if (keycode == 0 || keycode == 2)
		a->is_rotating = 0;
	else if (keycode == 257)
		a->is_sprinting = 0;
	else if (keycode == 46)
		music_manager(a);
	reload_window(a);
	return (0);
}

void	music_manager(t_all *a)
{
	if (a->is_music_playing == 0)
	{
		system("afplay mp3/music.mp3&");
		a->is_music_playing = 1;
	}
	else
	{
		system("killall afplay");
		a->is_music_playing = 0;
	}
}

int		reload_window(t_all *a)
{
	if (a->is_sprinting == 1)
		a->ms = 0.2;
	else
		a->ms = 0.1;
	move(a, a->is_moving);
	rotate(a, a->is_rotating);
	load_window(a);
	return (0);
}
