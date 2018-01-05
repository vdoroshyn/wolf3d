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


#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int		my_key_func1(int keycode, t_all *a)
{
	if (keycode == 53)
		proper_exit(a);
	else if (keycode == 123 || keycode == 124
		|| keycode == 125 || keycode == 126)
	{
		move(a, keycode);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_all a;

	construct(&a);
	a.dirX = -1;
	a.dirY = 0;
	a.planeX = 0;
	a.planeY = 0.66;
	a.posX = 22;
	a.posY = 12;
	a.time = 0;
	a.oldTime = 0;
	// double posX = 22, posY = 12;  //x and y start position
	// double dirX = -1, dirY = 0; //initial direction vector
	// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

create_new_image(&a);
for(int x = 0; x < a.win_x; x++)
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

	
	a.cameraX = 2 * x / (double)a.win_x - 1; //x-coordinate in camera space
	a.rayPosX = a.posX;
	a.rayPosY = a.posY;
	a.rayDirX = a.dirX + a.planeX * a.cameraX;
	a.rayDirY = a.dirY + a.planeY * a.cameraX;
	a.mapX = (int)a.rayPosX;
	a.mapY = (int)a.rayPosY;
	a.deltaDistX = sqrt(1 + (a.rayDirY * a.rayDirY) / (a.rayDirX * a.rayDirX));
	a.deltaDistY = sqrt(1 + (a.rayDirX * a.rayDirX) / (a.rayDirY * a.rayDirY));
	a.hit = 0;

	//calculate step and initial sideDist
	if (a.rayDirX < 0)
	{
		a.stepX = -1;
		a.sideDistX = (a.rayPosX - a.mapX) * a.deltaDistX;
	}
	else
	{
		a.stepX = 1;
		a.sideDistX = (a.mapX + 1.0 - a.rayPosX) * a.deltaDistX;
	}
	if (a.rayDirY < 0)
	{
		a.stepY = -1;
		a.sideDistY = (a.rayPosY - a.mapY) * a.deltaDistY;
	}
	else
	{
		a.stepY = 1;
		a.sideDistY = (a.mapY + 1.0 - a.rayPosY) * a.deltaDistY;
	}
	//perform DDA
	while (a.hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (a.sideDistX < a.sideDistY)
		{
			a.sideDistX += a.deltaDistX;
			a.mapX += a.stepX;
			a.side = 0;
		}
		else
		{
			a.sideDistY += a.deltaDistY;
			a.mapY += a.stepY;
			a.side = 1;
		}
		//Check if ray has hit a wall
		if (worldMap[a.mapX][a.mapY] > 0) a.hit = 1;
	}
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if (a.side == 0) a.perpWallDist = (a.mapX - a.rayPosX + (1 - a.stepX) / 2) / a.rayDirX;
	else           a.perpWallDist = (a.mapY - a.rayPosY + (1 - a.stepY) / 2) / a.rayDirY;

	//Calculate height of line to draw on screen
	int lineHeight = (int)(a.win_y / a.perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + a.win_y / 2;
	if(drawStart < 0)drawStart = 0;
	int drawEnd = lineHeight / 2 + a.win_y / 2;
	if(drawEnd >= a.win_y)drawEnd = a.win_y - 1;

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

	int i = 0;

	while (i < a.win_y)
	{	
		int pixel;
		t_color color;

		pixel = x * 4 + i * a.size_line;
		if (i < drawStart)
		{
			color.transp = 0;
			color.red = 000;
			color.green = 127;
			color.blue = 200;
			color_one_pixel(&a, pixel, color);
		}
		if (i >= drawStart && i <= drawEnd)
		{
			if (a.side == 0)
			{
				if (a.stepX > 0)
				{
					color.transp = 0;
					color.red = 255;
					color.green = 255;
					color.blue = 255;
				}
				else
				{
					color.transp = 0;
					color.red = 192;
					color.green = 192;
					color.blue = 192;
				}
			}
			else
			{
				if (a.stepY > 0)
				{
					color.transp = 0;
					color.red = 127;
					color.green = 127;
					color.blue = 127;
				}
				else {
					color.transp = 0;
					color.red = 64;
					color.green = 64;
					color.blue = 64;
				}

			}
			color_one_pixel(&a, pixel, color);
		}
		if (i > drawEnd)
		{	
			color.transp = 0;
			color.red = 55;
			color.green = 55;
			color.blue = 25;
			color_one_pixel(&a, pixel, color);
		}
		++i;
	}
}
//timing for input and FPS counter
// oldTime = time;
// time = getTicks();
// double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
// print(1.0 / frameTime); //FPS counter
// redraw();
// cls();

// //speed modifiers
// double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
// double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
a.oldTime = a.time;
a.time = clock();
a.frameTime = (a.time - a.oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
// print(1.0 / frameTime); //FPS counter
//speed modifiers
a.moveSpeed = a.frameTime * 5.0; //the constant value is in squares/second
a.rotSpeed = a.frameTime * 3.0; //the constant value is in radians/second
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
// }
	image_to_window_and_destroy(&a);
	mlx_hook(a.win, 2, 5, my_key_func1, &a);
	mlx_hook(a.win, 17, 1L << 17, proper_exit, &a);
	mlx_loop(a.mlx);
}
