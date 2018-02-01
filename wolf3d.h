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
	int				map_w;
	int				map_h;
	char			**map;
	int				win_x;
	int				win_y;
	void			*mlx;
	void			*win;
	void			*img;
	char			*str;
	int				bpp;
	int				size_line;
	int				endian;

	double			direction_x;
	double			direction_y;
	double			perp_dir_x;
	double			perp_dir_y;
	double			position_x;
	double			position_y;
	double			time;
	double			old_time;

	double			camera_x;
	double			ray_position_x;
	double			ray_position_y;
	double			ray_direction_x;
	double			ray_direction_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;

	double			wall_x;
	int				tex_x;

	int				x_step;
	int				y_step;
	int				hit;
	int				side;

	double			delta_time;
	double			ms;
	double			rotation_speed;

	int				is_sprinting;
	int				is_moving;
	int				is_rotating;

	int				is_music_playing;

	int				tex_bpp;
	int				tex_sl;
	int				tex_e;
	char			*wood;
	char			*redbrick;
	char			*greystone;
	char			*purplestone;
	char			*colorstone;
	char			*mossy;
	char			*gun;
}					t_all;

typedef struct		s_color
{
	unsigned char	transp;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_color;

void				construct(t_all *a);
void				destruct(t_all *a);
void				create_new_image(t_all *a);
void				image_to_window_and_destroy(t_all *a);
void				free_map(t_all *a);
int					proper_exit(t_all *a);

void				read_file_1(char *str, t_all *a);
void				create_pointer_map_array(t_all *a);
void				read_file_2(char *str, t_all *a);
int					are_all_map_borders_valid(t_all *a);
int					is_player(char c);

void				move(t_all *a, int flag);
void				rotate(t_all *a, int flag);

void				music_manager(t_all *a);

void				color_one_pixel(t_all *a, int pixel, t_color color);
void				draw(t_all *a, int x);
void				draw_minimap(t_all *a);

int					reload_window(t_all *a);
void				load_window(t_all *a);

void				load_gun(t_all *a);
void				load_textures(t_all *a);

#endif
