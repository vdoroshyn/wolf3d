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
	int lineHeight = (int)(a->win_y / a->perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + a->win_y / 2;
	if(drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + a->win_y / 2;
	if(drawEnd >= a->win_y)
		drawEnd = a->win_y - 1;

	int y;

	y = drawStart;
	while (y < drawEnd)
	{
		pixel = x * 4 + y * a->size_line;
		int d = y * 256 - a->win_y * 128 + lineHeight * 128;
		int texY = ((d * 64) / lineHeight) / 256;

		if (a->side == 0)
		{
			if (a->x_step > 0)
			{
				color.transp = 0;
				color.red = (unsigned char)(a->wood[(64 * texY + a->tex_x) * 4 + 2]) / 2;
				color.green = (unsigned char)(a->wood[((64 * texY + a->tex_x) * 4) + 1]) / 2;
				color.blue = (unsigned char)(a->wood[((64 * texY + a->tex_x) * 4) + 0]) / 2;
			}
			else
			{
				color.transp = 0;
				color.red = a->mossy[(64 * texY + a->tex_x) * 4 + 2];
				color.green = a->mossy[((64 * texY + a->tex_x) * 4) + 1];
				color.blue = a->mossy[((64 * texY + a->tex_x) * 4) + 0];
			}
		}
		else
		{
			if (a->y_step > 0)
			{
				color.transp = 0;
				color.red = a->greystone[(64 * texY + a->tex_x) * 4 + 2];
				color.green = a->greystone[((64 * texY + a->tex_x) * 4) + 1];
				color.blue = a->greystone[((64 * texY + a->tex_x) * 4) + 0];
			}
			else
			{
				color.transp = 0;
				color.red = a->colorstone[(64 * texY + a->tex_x) * 4 + 2];
				color.green = a->colorstone[((64 * texY + a->tex_x) * 4) + 1];
				color.blue = a->colorstone[((64 * texY + a->tex_x) * 4) + 0];
			}
		}

		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// if(side == 1) color = (color >> 1) & 8355711;
		color_one_pixel(a, pixel, color);
		++y;
	}

	//FLOOR CASTING
	double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

	//4 different wall directions possible
	if(a->side == 0 && a->ray_direction_x > 0)
	{
		floorXWall = a->map_x;
		floorYWall = a->map_y + a->wall_x;
	}
	else if(a->side == 0 && a->ray_direction_x < 0)
	{
		floorXWall = a->map_x + 1.0;
		floorYWall = a->map_y + a->wall_x;
	}
	else if(a->side == 1 && a->ray_direction_y > 0)
	{
		floorXWall = a->map_x + a->wall_x;
		floorYWall = a->map_y;
	}
	else
	{
		floorXWall = a->map_x + a->wall_x;
		floorYWall = a->map_y + 1.0;
	}

	double distWall;
	double distPlayer;
	double currentDist;

	distWall = a->perp_wall_dist;
	distPlayer = 0.0;

	if (drawEnd < 0)
	drawEnd = a->win_y; //becomes < 0 when the integer overflows

	//draw the floor from drawEnd to the bottom of the screen
	y = drawEnd + 1;
	while (y < a->win_y)
	{
		currentDist = a->win_y / (2.0 * y - a->win_y); //you could make a small lookup table for this instead

		double weight = (currentDist - distPlayer) / (distWall - distPlayer);

		double currentFloorX = weight * floorXWall + (1.0 - weight) * a->position_x;
		double currentFloorY = weight * floorYWall + (1.0 - weight) * a->position_y;

		int floorTexX, floorTexY;
		floorTexX = (int)(currentFloorX * 64) % 64;
		floorTexY = (int)(currentFloorY * 64) % 64;

		//floor
		pixel = x * 4 + y * a->size_line;
		color.transp = 0;
		color.red = a->purplestone[(64 * floorTexY + floorTexX) * 4 + 2];
		color.green = a->purplestone[((64 * floorTexY + floorTexX) * 4) + 1];
		color.blue = a->purplestone[((64 * floorTexY + floorTexX) * 4) + 0];
		color_one_pixel(a, pixel, color);
		//ceiling (symmetrical!)
		pixel = x * 4 + (a->win_y - y) * a->size_line;
		color.transp = 0;
		color.red = a->redbrick[(64 * floorTexY + floorTexX) * 4 + 2];
		color.green = a->redbrick[((64 * floorTexY + floorTexX) * 4) + 1];
		color.blue = a->redbrick[((64 * floorTexY + floorTexX) * 4) + 0];
		color_one_pixel(a, pixel, color);
		++y;
	}
}
