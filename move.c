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

// void			move(t_all *a, int keycode)
// {
// 	if (keycode == 123)
// 	{
// 		  double oldDirX = a->dirX;
// 		  a->dirX = a->dirX * cos(a->rotSpeed) - a->dirY * sin(a->rotSpeed);
// 		  a->dirY = oldDirX * sin(a->rotSpeed) + a->dirY * cos(a->rotSpeed);
// 		  double oldPlaneX = a->planeX;
// 		  a->planeX = a->planeX * cos(a->rotSpeed) - a->planeY * sin(a->rotSpeed);
// 		  a->planeY = oldPlaneX * sin(a->rotSpeed) + a->planeY * cos(a->rotSpeed);
// 	}
// 	else if (keycode == 124)
// 	{
// 		  double oldDirX = a->dirX;
// 		  a->dirX = a->dirX * cos(-a->rotSpeed) - a->dirY * sin(-a->rotSpeed);
// 		  a->dirY = oldDirX * sin(-a->rotSpeed) + a->dirY * cos(-a->rotSpeed);
// 		  double oldPlaneX = a->planeX;
// 		  a->planeX = a->planeX * cos(-a->rotSpeed) - a->planeY * sin(-a->rotSpeed);
// 		  a->planeY = oldPlaneX * sin(-a->rotSpeed) + a->planeY * cos(-a->rotSpeed);
// 	}
// 	else if (keycode == 125)
// 	{
// 		if(!(worldMap[(int)(a->posX - a->dirX * a->moveSpeed)][(int)a->posY]))
// 			a->posX -= a->dirX * a->moveSpeed;
//   		if(!(worldMap[(int)a->posX][(int)(a->posY - a->dirY * a->moveSpeed)]))
//   			a->posY -= a->dirY * a->moveSpeed;
// 	}
// 	else if (keycode == 126)
// 	{
// 		if(!(worldMap[(int)(a->posX + a->dirX * a->moveSpeed)][(int)a->posY]))
// 			a->posX += a->dirX * a->moveSpeed;
//  		if(!(worldMap[(int)a->posX][(int)(a->posY + a->dirY * a->moveSpeed)]))
//  			a->posY += a->dirY * a->moveSpeed;
// 	}
// }
