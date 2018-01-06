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
	//Calculate height of line to draw on screen
	int lineHeight = (int)(a->win_y / a->perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + a->win_y / 2;
	if(drawStart < 0)drawStart = 0;
	int drawEnd = lineHeight / 2 + a->win_y / 2;
	if(drawEnd >= a->win_y)drawEnd = a->win_y - 1;

	int i = 0;

	while (i < a->win_y)
	{	
		int pixel;
		t_color color;

		pixel = x * 4 + i * a->size_line;
		if (i < drawStart)
		{
			color.transp = 0;
			color.red = 000;
			color.green = 127;
			color.blue = 200;
			color_one_pixel(a, pixel, color);
		}
		if (i >= drawStart && i <= drawEnd)
		{
			if (a->side == 0)
			{
				if (a->stepX > 0)
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
				if (a->stepY > 0)
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
			color_one_pixel(a, pixel, color);
		}
		if (i > drawEnd)
		{	
			color.transp = 0;
			color.red = 55;
			color.green = 55;
			color.blue = 25;
			color_one_pixel(a, pixel, color);
		}
		++i;
	}

}
