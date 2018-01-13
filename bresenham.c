/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:03:15 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/09 16:03:27 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		color_one_pixel(t_all *a, int pixel, t_color color)
{
	// int			i;

	// if (x < 0 || y < 0 || x > a->win_x - 1 || y > a->win_y - 1)
	// {
	// 	return ;
	// }
	// i = x * 4 + y * a->size_line;
	a->str[pixel] = color.blue;
	a->str[pixel + 1] = color.green;
	a->str[pixel + 2] = color.red;
	a->str[pixel + 3] = color.transp;
}

void	draw(t_all *a, int x)
{
	int pixel;
	t_color color;


	//Calculate height of line to draw on screen
	int lineHeight = (int)(a->win_y / a->perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + a->win_y / 2;
	if(drawStart < 0)drawStart = 0;
	int drawEnd = lineHeight / 2 + a->win_y / 2;
	if(drawEnd >= a->win_y)drawEnd = a->win_y - 1;

	for(int y = drawStart; y < drawEnd; y++)
	{


		pixel = x * 4 + y * a->size_line;
		int d = y * 256 - a->win_y * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
		int texY = ((d * 64) / lineHeight) / 256;

		if (a->side == 0)
		{
			if (a->stepX > 0)
			{
				color.transp = 0;
				color.red = (unsigned char)(a->wood[(64 * texY + a->texX) * 4 + 2]) / 2;
				color.green = (unsigned char)(a->wood[((64 * texY + a->texX) * 4) + 1]) / 2;
				color.blue = (unsigned char)(a->wood[((64 * texY + a->texX) * 4) + 0]) / 2;
				// printf("%u\n", color.red);
				// printf("%u\n", color.green);
				// printf("%u\n", color.blue);
				//exit(0);
			}
			else
			{
				color.transp = 0;
				color.red = a->mossy[(64 * texY + a->texX) * 4 + 2];
				color.green = a->mossy[((64 * texY + a->texX) * 4) + 1];
				color.blue = a->mossy[((64 * texY + a->texX) * 4) + 0];
			}
		}
		else
		{
			if (a->stepY > 0)
			{
				color.transp = 0;
				color.red = a->greystone[(64 * texY + a->texX) * 4 + 2];
				color.green = a->greystone[((64 * texY + a->texX) * 4) + 1];
				color.blue = a->greystone[((64 * texY + a->texX) * 4) + 0];
				// color.transp = 0;
				// color.red = a->redbrick[(64 * texY + a->texX) * 4 + 2];
				// color.green = a->redbrick[((64 * texY + a->texX) * 4) + 1];
				// color.blue = a->redbrick[((64 * texY + a->texX) * 4) + 0];
			}
			else
			{
				color.transp = 0;
				color.red = a->colorstone[(64 * texY + a->texX) * 4 + 2];
				color.green = a->colorstone[((64 * texY + a->texX) * 4) + 1];
				color.blue = a->colorstone[((64 * texY + a->texX) * 4) + 0];
			}
		}

		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// if(side == 1) color = (color >> 1) & 8355711;
		color_one_pixel(a, pixel, color);
	}

	//FLOOR CASTING
	double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

	//4 different wall directions possible
	if(a->side == 0 && a->rayDirX > 0)
	{
		floorXWall = a->mapX;
		floorYWall = a->mapY + a->wallX;
	}
	else if(a->side == 0 && a->rayDirX < 0)
	{
		floorXWall = a->mapX + 1.0;
		floorYWall = a->mapY + a->wallX;
	}
	else if(a->side == 1 && a->rayDirY > 0)
	{
		floorXWall = a->mapX + a->wallX;
		floorYWall = a->mapY;
	}
	else
	{
		floorXWall = a->mapX + a->wallX;
		floorYWall = a->mapY + 1.0;
	}

	double distWall, distPlayer, currentDist;

	distWall = a->perpWallDist;
	distPlayer = 0.0;

	if (drawEnd < 0) drawEnd = a->win_y; //becomes < 0 when the integer overflows

	//draw the floor from drawEnd to the bottom of the screen
	for(int y = drawEnd + 1; y < a->win_y; y++)
	{
		currentDist = a->win_y / (2.0 * y - a->win_y); //you could make a small lookup table for this instead

		double weight = (currentDist - distPlayer) / (distWall - distPlayer);

		double currentFloorX = weight * floorXWall + (1.0 - weight) * a->posX;
		double currentFloorY = weight * floorYWall + (1.0 - weight) * a->posY;

		int floorTexX, floorTexY;
		floorTexX = (int)(currentFloorX * 64) % 64;
		floorTexY = (int)(currentFloorY * 64) % 64;

		//floor
		//buffer[y][x] = (texture[3][64 * floorTexY + floorTexX] >> 1) & 8355711;
		//ceiling (symmetrical!)
		pixel = x * 4 + y * a->size_line;
		color.transp = 0;
		color.red = a->purplestone[(64 * floorTexY + floorTexX) * 4 + 2];
		color.green = a->purplestone[((64 * floorTexY + floorTexX) * 4) + 1];
		color.blue = a->purplestone[((64 * floorTexY + floorTexX) * 4) + 0];
		color_one_pixel(a, pixel, color);

		//buffer[a->win_y - y][x] = purplestone[64 * floorTexY + floorTexX];
	}

	for(int y = 0; y < drawStart; y++)
	{
		currentDist = a->win_y / (2.0 * y - a->win_y); //you could make a small lookup table for this instead

		double weight = (currentDist - distPlayer) / (distWall - distPlayer);

		double currentFloorX = weight * floorXWall + (1.0 - weight) * a->posX;
		double currentFloorY = weight * floorYWall + (1.0 - weight) * a->posY;

		int floorTexX, floorTexY;
		floorTexX = (int)(currentFloorX * 64) % 64;
		floorTexY = (int)(currentFloorY * 64) % 64;

		pixel = x * 4 + y * a->size_line;
		color.transp = 0;
		color.red = a->redbrick[(64 * floorTexY + floorTexX) * 4 + 2];
		color.green = a->redbrick[((64 * floorTexY + floorTexX) * 4) + 1];
		color.blue = a->redbrick[((64 * floorTexY + floorTexX) * 4) + 0];
		color_one_pixel(a, pixel, color);
	}

	// int i = 0;

	// while (i < a->win_y)
	// {	
	// 	int pixel;
	// 	t_color color;

	// 	pixel = x * 4 + i * a->size_line;
	// 	if (i < drawStart)
	// 	{
	// 		color.transp = 0;
	// 		color.red = 000;
	// 		color.green = 127;
	// 		color.blue = 200;
	// 		color_one_pixel(a, pixel, color);
	// 	}
	// 	if (i >= drawStart && i <= drawEnd)
	// 	{
	// 		if (a->side == 0)
	// 		{
	// 			if (a->stepX > 0)
	// 			{
	// 				color.transp = 0;
	// 				color.red = 255;
	// 				color.green = 255;
	// 				color.blue = 255;
	// 			}
	// 			else
	// 			{
	// 				color.transp = 0;
	// 				color.red = 192;
	// 				color.green = 192;
	// 				color.blue = 192;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			if (a->stepY > 0)
	// 			{
	// 				color.transp = 0;
	// 				color.red = 127;
	// 				color.green = 127;
	// 				color.blue = 127;
	// 			}
	// 			else {
	// 				color.transp = 0;
	// 				color.red = 64;
	// 				color.green = 64;
	// 				color.blue = 64;
	// 			}

	// 		}
	// 		color_one_pixel(a, pixel, color);
	// 	}
	// 	if (i > drawEnd)
	// 	{	
	// 		color.transp = 0;
	// 		color.red = 55;
	// 		color.green = 55;
	// 		color.blue = 25;
	// 		color_one_pixel(a, pixel, color);
	// 	}
	// 	++i;
	// }

}
