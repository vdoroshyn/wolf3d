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

void			move(t_all *a, int keycode)
{
	if (keycode == 123)
	{
		  double oldDirX = dirX;
		  dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		  dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		  double oldPlaneX = planeX;
		  planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		  planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	else if (keycode == 124)
	{
		  double oldDirX = dirX;
		  dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		  dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		  double oldPlaneX = planeX;
		  planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		  planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	else if (keycode == 125)
	{
		if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
  		if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	else if (keycode == 126)
	{
		if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
 		if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}
}
