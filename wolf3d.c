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


// #define mapWidth 24
// #define mapHeight 24

// int worldMap[mapWidth][mapHeight]=
// {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

int		key_press(int keycode, t_all *a)
{
	if (keycode == 53)
		proper_exit(a);
	else if (keycode == 125)
		a->is_moving = 1;
	else if (keycode == 126)
		a->is_moving = 2;
	else if (keycode == 123)
		a->is_rotating = 1;
	else if (keycode == 124)
		a->is_rotating = 2;
	else if (keycode == 257)
		a->is_sprinting = 1;
	reload_window(a);
	return (0);
}

int		key_release(int keycode, t_all *a)
{
	if (keycode == 125 || keycode == 126)
		a->is_moving = 0;
	else if (keycode == 123 || keycode == 124)
		a->is_rotating = 0;
	else if (keycode == 257)
		a->is_sprinting = 0;
	reload_window(a);
	return (0);
}

int		reload_window(t_all *a)
{
	if (a->is_sprinting == 1)
		a->moveSpeed = 0.2;
	else
		a->moveSpeed = 0.1;
	move(a, a->is_moving);
	rotate(a, a->is_rotating);
	load_window(a);
	return (0);
}

void				load_window(t_all *a)
{
	create_new_image(a);
	for(int x = 0; x < a->win_x; x++)
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

		
		a->cameraX = 2 * x / (double)a->win_x - 1; //x-coordinate in camera space
		a->rayPosX = a->posX;
		a->rayPosY = a->posY;
		a->rayDirX = a->dirX + a->planeX * a->cameraX;
		a->rayDirY = a->dirY + a->planeY * a->cameraX;
		a->mapX = (int)a->rayPosX;
		a->mapY = (int)a->rayPosY;
		a->deltaDistX = sqrt(1 + (a->rayDirY * a->rayDirY) / (a->rayDirX * a->rayDirX));
		a->deltaDistY = sqrt(1 + (a->rayDirX * a->rayDirX) / (a->rayDirY * a->rayDirY));
		a->hit = 0;

		//calculate step and initial sideDist
		if (a->rayDirX < 0)
		{
			a->stepX = -1;
			a->sideDistX = (a->rayPosX - a->mapX) * a->deltaDistX;
		}
		else
		{
			a->stepX = 1;
			a->sideDistX = (a->mapX + 1.0 - a->rayPosX) * a->deltaDistX;
		}
		if (a->rayDirY < 0)
		{
			a->stepY = -1;
			a->sideDistY = (a->rayPosY - a->mapY) * a->deltaDistY;
		}
		else
		{
			a->stepY = 1;
			a->sideDistY = (a->mapY + 1.0 - a->rayPosY) * a->deltaDistY;
		}
		//perform DDA
		while (a->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (a->sideDistX < a->sideDistY)
			{
				a->sideDistX += a->deltaDistX;
				a->mapX += a->stepX;
				a->side = 0;
			}
			else
			{
				a->sideDistY += a->deltaDistY;
				a->mapY += a->stepY;
				a->side = 1;
			}
			//Check if ray has hit a wall
			if (a->map[a->mapX][a->mapY] > '0') a->hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (a->side == 0) a->perpWallDist = (a->mapX - a->rayPosX + (1 - a->stepX) / 2) / a->rayDirX;
		else           a->perpWallDist = (a->mapY - a->rayPosY + (1 - a->stepY) / 2) / a->rayDirY;



		// //choose wall color
		// ColorRGB color;
		// switch(worldMap[mapX][mapY])
		// {
		// 	case 1:  color = RGB_Red;  break; //red
		// 	case 2:  color = RGB_Green;  break; //green
		// 	case 3:  color = RGB_Blue;   break; //blue
		// 	case 4:  color = RGB_White;  break; //white
		// 	default: color = RGB_Yellow; break; //yellow
		// }

		// //give x and y sides different brightness
		// if (side == 1) {color = color / 2;}
		
		// t_color color;

		// color.transp = 0;
		// color.red = 255;
		// color.green = 0;
		// color.blue = 0;
		//draw the pixels of the stripe as a vertical line
		// t_br1 coord;

		// coord.x0 = x;
		// coord.x1 = x;
		// coord.y0 = drawStart;
		// coord.y1 = drawEnd;
		draw(a, x);
	}
	image_to_window_and_destroy(a);
	load_gun(a);
}

void			move(t_all *a, int flag)
{
	if (flag == 1)
	{
		if((a->map[(int)(a->posX - a->dirX * a->moveSpeed)][(int)a->posY]) == '0')
			a->posX -= a->dirX * a->moveSpeed;
  		if((a->map[(int)a->posX][(int)(a->posY - a->dirY * a->moveSpeed)]) == '0')
  			a->posY -= a->dirY * a->moveSpeed;
	}
	else if (flag == 2)
	{
		if((a->map[(int)(a->posX + a->dirX * a->moveSpeed)][(int)a->posY]) == '0')
			a->posX += a->dirX * a->moveSpeed;
 		if((a->map[(int)a->posX][(int)(a->posY + a->dirY * a->moveSpeed)]) == '0')
 			a->posY += a->dirY * a->moveSpeed;
	}
}

void			rotate(t_all *a, int flag)
{
	if (flag == 1)
	{
		  double oldDirX = a->dirX;
		  a->dirX = a->dirX * cos(a->rotSpeed) - a->dirY * sin(a->rotSpeed);
		  a->dirY = oldDirX * sin(a->rotSpeed) + a->dirY * cos(a->rotSpeed);
		  double oldPlaneX = a->planeX;
		  a->planeX = a->planeX * cos(a->rotSpeed) - a->planeY * sin(a->rotSpeed);
		  a->planeY = oldPlaneX * sin(a->rotSpeed) + a->planeY * cos(a->rotSpeed);
	}
	else if (flag == 2)
	{
		  double oldDirX = a->dirX;
		  a->dirX = a->dirX * cos(-a->rotSpeed) - a->dirY * sin(-a->rotSpeed);
		  a->dirY = oldDirX * sin(-a->rotSpeed) + a->dirY * cos(-a->rotSpeed);
		  double oldPlaneX = a->planeX;
		  a->planeX = a->planeX * cos(-a->rotSpeed) - a->planeY * sin(-a->rotSpeed);
		  a->planeY = oldPlaneX * sin(-a->rotSpeed) + a->planeY * cos(-a->rotSpeed);
	}
}

void	load_textures(t_all *a)
{
	void *textures[6];
	int width;
	int height;

	textures[0] = mlx_xpm_file_to_image(a->mlx, "textures/wood.xpm", &width, &height);
	textures[1] = mlx_xpm_file_to_image(a->mlx, "textures/redbrick.xpm", &width, &height);
	textures[2] = mlx_xpm_file_to_image(a->mlx, "textures/greystone.xpm", &width, &height);
	textures[3] = mlx_xpm_file_to_image(a->mlx, "textures/purplestone.xpm", &width, &height);
	textures[4] = mlx_xpm_file_to_image(a->mlx, "textures/colorstone.xpm", &width, &height);
	textures[5] = mlx_xpm_file_to_image(a->mlx, "textures/mossy.xpm", &width, &height);

	a->wood = mlx_get_data_addr(textures[0], &a->tex_bpp, &a->tex_size_line, &a->tex_endian);
	a->redbrick = mlx_get_data_addr(textures[1], &a->tex_bpp, &a->tex_size_line, &a->tex_endian);
	a->greystone = mlx_get_data_addr(textures[2], &a->tex_bpp, &a->tex_size_line, &a->tex_endian);
	a->purplestone = mlx_get_data_addr(textures[3], &a->tex_bpp, &a->tex_size_line, &a->tex_endian);
	a->colorstone = mlx_get_data_addr(textures[4], &a->tex_bpp, &a->tex_size_line, &a->tex_endian);
	a->mossy = mlx_get_data_addr(textures[5], &a->tex_bpp, &a->tex_size_line, &a->tex_endian);
}

void		load_gun(t_all *a)
{
	void	*gun_texture[1];
	int gun_width;
	int gun_height;

	gun_texture[0] = mlx_xpm_file_to_image(a->mlx, "textures/gun.xpm", &gun_width, &gun_height);
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
	a.dirX = -1;
	a.dirY = 0;
	a.planeX = 0;
	a.planeY = 0.66;
	// a.posX = 22;
	// a.posY = 12;
	a.time = 0;
	a.oldTime = 0;

	a.is_rotating = 0;
	a.is_moving = 0;
	a.is_sprinting = 0;
	
	// double posX = 22, posY = 12;  //x and y start position
	// double dirX = -1, dirY = 0; //initial direction vector
	// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

//timing for input and FPS counter
// oldTime = time;
// time = getTicks();
// double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
// print(1.0 / frameTime); //FPS counter
// redraw();
// cls();
load_window(&a);
// //speed modifiers
// double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
// double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
a.oldTime = a.time;
a.time = clock();
a.frameTime = (a.time - a.oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
// print(1.0 / frameTime); //FPS counter
//speed modifiers
// a.moveSpeed = a.frameTime * 5.0; //the constant value is in squares/second
// a.rotSpeed = a.frameTime * 3.0; //the constant value is in radians/second
a.moveSpeed = 0.1;
a.rotSpeed = 0.05;
// readKeys();
// //move forward if no wall in front of you
// if (keyDown(SDLK_UP))
// {
//   if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
//   if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
// }
// //move backwards if no wall behind you
// if (keyDown(SDLK_DOWN))
// {
//   if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
//   if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
// }
// //rotate to the right
// if (keyDown(SDLK_RIGHT))
// {
//   //both camera direction and camera plane must be rotated
//   double oldDirX = dirX;
//   dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//   dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//   double oldPlaneX = planeX;
//   planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//   planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
// }
// //rotate to the left
// if (keyDown(SDLK_LEFT))
// {
//   //both camera direction and camera plane must be rotated
//   double oldDirX = dirX;
//   dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//   dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//   double oldPlaneX = planeX;
//   planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//   planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	// mlx_hook(a.win, 2, 5, my_key_func1, &a);
	mlx_hook(a.win, 2, 1, key_press, &a);
	mlx_hook(a.win, 3, 2, key_release, &a);
	mlx_hook(a.win, 17, 1L << 17, proper_exit, &a);
	mlx_loop_hook(a.mlx, reload_window, &a);
	mlx_loop(a.mlx);
}
