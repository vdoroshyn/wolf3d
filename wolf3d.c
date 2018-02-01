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

void				load_window(t_all *a)
{
	create_new_image(a);
	int x;

	x = 0;
	while (x < a->win_x)
	{
		// //calculate ray position and direction
		// double cameraX = 2 * x / (double)a.win_x - 1; //x-coordinate in camera space
		// double rayPosX = a.posX;
		// double rayPosY = a.posY;
		// double rayDirX = a.dirX + a.planeX * cameraX;
		// double rayDirY = a.dirY + a.planeY * cameraX;
		// //which box of the map we're in
		// int mapX = (int)rayPosX;
		// int mapY = (int)rayPosY;

		// //length of ray from current position to next x or y-side
		// double sideDistX;
		// double sideDistY;

		// //length of ray from one x or y-side to next x or y-side
		// double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		// double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		// double perpWallDist;

		// //what direction to step in x or y-direction (either +1 or -1)
		// int stepX;
		// int stepY;

		// int hit = 0; //was there a wall hit?
		// int side; //was a NS or a EW wall hit? NSWE

		
		a->camera_x = 2 * x / (double)a->win_x - 1; //x-coordinate in camera space
		a->ray_position_x = a->position_x;
		a->ray_position_y = a->position_y;
		a->ray_direction_x = a->direction_x + a->perp_dir_x * a->camera_x;
		a->ray_direction_y = a->direction_y + a->perp_dir_y * a->camera_x;
		a->map_x = (int)a->ray_position_x;
		a->map_y = (int)a->ray_position_y;
		a->delta_dist_x = sqrt(1 + (a->ray_direction_y * a->ray_direction_y) / (a->ray_direction_x * a->ray_direction_x));
		a->delta_dist_y = sqrt(1 + (a->ray_direction_x * a->ray_direction_x) / (a->ray_direction_y * a->ray_direction_y));
		a->hit = 0;

		//calculate step and initial sideDist
		if (a->ray_direction_x < 0)
		{
			a->x_step = -1;
			a->side_dist_x = (a->ray_position_x - a->map_x) * a->delta_dist_x;
		}
		else
		{
			a->x_step = 1;
			a->side_dist_x = (a->map_x + 1.0 - a->ray_position_x) * a->delta_dist_x;
		}
		if (a->ray_direction_y < 0)
		{
			a->y_step = -1;
			a->side_dist_y = (a->ray_position_y - a->map_y) * a->delta_dist_y;
		}
		else
		{
			a->y_step = 1;
			a->side_dist_y = (a->map_y + 1.0 - a->ray_position_y) * a->delta_dist_y;
		}
		//perform DDA
		while (a->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
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
			//Check if ray has hit a wall
			if (a->map[a->map_x][a->map_y] > '0')
				a->hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (a->side == 0)
			a->perp_wall_dist = (a->map_x - a->ray_position_x + (1 - a->x_step) / 2) / a->ray_direction_x;
		else
			a->perp_wall_dist = (a->map_y - a->ray_position_y + (1 - a->y_step) / 2) / a->ray_direction_y;


		//calculate value of wallX
		//double wallX; //where exactly the wall was hit
		if (a->side == 0)
			a->wall_x = a->ray_position_y + a->perp_wall_dist * a->ray_direction_y;
		else
			a->wall_x = a->ray_position_x + a->perp_wall_dist * a->ray_direction_x;
		a->wall_x -= floor((a->wall_x));

		//x coordinate on the texture
		a->tex_x = (int)(a->wall_x * (double)64);
		if(a->side == 0 && a->ray_direction_x > 0)
			a->tex_x = 64 - a->tex_x - 1;
		if(a->side == 1 && a->ray_direction_y < 0)
			a->tex_x = 64 - a->tex_x - 1;
		draw(a, x);
		++x;
	}
	draw_minimap(a);
	image_to_window_and_destroy(a);
	load_gun(a);
	
}

void			move(t_all *a, int flag)
{
	if (flag == 1)
	{
		if((a->map[(int)(a->position_x - (a->direction_x * a->ms) * 3)][(int)a->position_y]) == '0')
			a->position_x -= a->direction_x * a->ms;
  		if((a->map[(int)a->position_x][(int)(a->position_y - (a->direction_y * a->ms) * 3)]) == '0')
  			a->position_y -= a->direction_y * a->ms;
	}
	else if (flag == 2)
	{
		if((a->map[(int)(a->position_x + (a->direction_x * a->ms) * 3)][(int)a->position_y]) == '0')
			a->position_x += a->direction_x * a->ms;
 		if((a->map[(int)a->position_x][(int)(a->position_y + (a->direction_y * a->ms) * 3)]) == '0')
 			a->position_y += a->direction_y * a->ms;
	}
	else if (flag == 3)
	{
		if((a->map[(int)(a->position_x - (a->perp_dir_x * a->ms) * 3)][(int)a->position_y]) == '0')
			a->position_x -= a->perp_dir_x * a->ms;
  		if((a->map[(int)a->position_x][(int)(a->position_y - (a->perp_dir_y * a->ms) * 3)]) == '0')
  			a->position_y -= a->perp_dir_y * a->ms;
	}
	else if (flag == 4)
	{
		if((a->map[(int)(a->position_x + (a->perp_dir_x * a->ms) * 3)][(int)a->position_y]) == '0')
			a->position_x += a->perp_dir_x * a->ms;
 		if((a->map[(int)a->position_x][(int)(a->position_y + (a->perp_dir_y * a->ms) * 3)]) == '0')
 			a->position_y += a->perp_dir_y * a->ms;
	}
}

void			rotate(t_all *a, int flag)
{
	if (flag == 1)
	{
		  double oldDirX = a->direction_x;
		  a->direction_x = a->direction_x * cos(a->rotation_speed) - a->direction_y * sin(a->rotation_speed);
		  a->direction_y = oldDirX * sin(a->rotation_speed) + a->direction_y * cos(a->rotation_speed);
		  double oldPlaneX = a->perp_dir_x;
		  a->perp_dir_x = a->perp_dir_x * cos(a->rotation_speed) - a->perp_dir_y * sin(a->rotation_speed);
		  a->perp_dir_y = oldPlaneX * sin(a->rotation_speed) + a->perp_dir_y * cos(a->rotation_speed);
	}
	else if (flag == 2)
	{
		  double oldDirX = a->direction_x;
		  a->direction_x = a->direction_x * cos(-a->rotation_speed) - a->direction_y * sin(-a->rotation_speed);
		  a->direction_y = oldDirX * sin(-a->rotation_speed) + a->direction_y * cos(-a->rotation_speed);
		  double oldPlaneX = a->perp_dir_x;
		  a->perp_dir_x = a->perp_dir_x * cos(-a->rotation_speed) - a->perp_dir_y * sin(-a->rotation_speed);
		  a->perp_dir_y = oldPlaneX * sin(-a->rotation_speed) + a->perp_dir_y * cos(-a->rotation_speed);
	}
}

void	load_textures(t_all *a)
{
	void *tex[6];
	int w;
	int h;

	tex[0] = mlx_xpm_file_to_image(a->mlx, "tex/wood.xpm", &w, &h);
	tex[1] = mlx_xpm_file_to_image(a->mlx, "tex/redbrick.xpm", &w, &h);
	tex[2] = mlx_xpm_file_to_image(a->mlx, "tex/greystone.xpm", &w, &h);
	tex[3] = mlx_xpm_file_to_image(a->mlx, "tex/purplestone.xpm", &w, &h);
	tex[4] = mlx_xpm_file_to_image(a->mlx, "tex/colorstone.xpm", &w, &h);
	tex[5] = mlx_xpm_file_to_image(a->mlx, "tex/mossy.xpm", &w, &h);

	a->wood = mlx_get_data_addr(tex[0], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->redbrick = mlx_get_data_addr(tex[1], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->greystone = mlx_get_data_addr(tex[2], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->purplestone = mlx_get_data_addr(tex[3], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->colorstone = mlx_get_data_addr(tex[4], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->mossy = mlx_get_data_addr(tex[5], &a->tex_bpp, &a->tex_sl, &a->tex_e);
}

void		load_gun(t_all *a)
{
	void	*gun_texture[1];
	int gun_width;
	int gun_height;

	gun_texture[0] = mlx_xpm_file_to_image(a->mlx, "tex/gun.xpm", &gun_width, &gun_height);
	mlx_put_image_to_window(a->mlx, a->win, gun_texture[0], (a->win_x - gun_width) / 4 * 3, a->win_y - gun_height);
	mlx_destroy_image(a->mlx, gun_texture[0]);
}

int main(int argc, char **argv)
{
	t_all a;

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

	a.direction_x = -1;
	a.direction_y = 0;
	a.perp_dir_x = 0;
	a.perp_dir_y = 0.66;
	a.time = 0;
	a.old_time = 0;

	a.is_rotating = 0;
	a.is_moving = 0;
	a.is_sprinting = 0;
	a.is_music_playing = 0;

	load_window(&a);

	a.old_time = a.time;
	a.time = clock();
	a.delta_time = (a.time - a.old_time) / 1000.0;
	a.ms = a.delta_time * 5.0;
	a.rotation_speed = a.delta_time * 0.001;

	mlx_hook(a.win, 2, 1, key_press, &a);
	mlx_hook(a.win, 3, 2, key_release, &a);
	mlx_hook(a.win, 17, 1L << 17, proper_exit, &a);
	mlx_loop_hook(a.mlx, reload_window, &a);
	mlx_loop(a.mlx);
}
