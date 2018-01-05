/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:05:44 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/16 14:28:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "mlx.h"
# include <time.h>

typedef struct		s_all
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*str;
	int				bpp;
	int				size_line;
	int				endian;
	int				win_x;
	int				win_y;
	
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double			posX;
	double			posY;
	double			time;
	double			oldTime;

	double			cameraX;
	double			rayPosX;
	double			rayPosY;
	double			rayDirX;
	double			rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;

	int stepX;
	int stepY;
	int hit;
	int side;

	double frameTime;
	double moveSpeed;
	double rotSpeed;

}					t_all;

typedef struct		s_color
{
	unsigned char	transp;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_color;

typedef struct		s_br1
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
}					t_br1;

typedef struct		s_br2
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
}					t_br2;

void				construct(t_all *a);
void				destruct(t_all *a);
void				create_new_image(t_all *a);
void				image_to_window_and_destroy(t_all *a);
int					proper_exit(t_all *a);

void				move(t_all *a, int keycode);

void				color_one_pixel(t_all *a, int pixel, t_color color);
// void			segment(t_br1 coord, t_all a, t_color color);
#endif
