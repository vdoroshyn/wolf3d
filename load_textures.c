/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:05:44 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/16 14:28:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		load_textures(t_all *a)
{
	void	*tex[6];
	int		w;
	int		h;

	tex[0] = mlx_xpm_file_to_image(a->mlx, "tex/wood.xpm", &w, &h);
	tex[1] = mlx_xpm_file_to_image(a->mlx, "tex/redbrick.xpm", &w, &h);
	tex[2] = mlx_xpm_file_to_image(a->mlx, "tex/greystone.xpm", &w, &h);
	tex[3] = mlx_xpm_file_to_image(a->mlx, "tex/purplestone.xpm", &w, &h);
	tex[4] = mlx_xpm_file_to_image(a->mlx, "tex/colorstone.xpm", &w, &h);
	tex[5] = mlx_xpm_file_to_image(a->mlx, "tex/mossy.xpm", &w, &h);
	a->wd = mlx_get_data_addr(tex[0], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->rb = mlx_get_data_addr(tex[1], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->gs = mlx_get_data_addr(tex[2], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->ps = mlx_get_data_addr(tex[3], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->cs = mlx_get_data_addr(tex[4], &a->tex_bpp, &a->tex_sl, &a->tex_e);
	a->m = mlx_get_data_addr(tex[5], &a->tex_bpp, &a->tex_sl, &a->tex_e);
}

void		load_gun(t_all *a)
{
	void	*gun_text[1];
	int		gun_w;
	int		gun_h;

	gun_text[0] = mlx_xpm_file_to_image(a->mlx, "tex/gun.xpm", &gun_w, &gun_h);
	mlx_put_image_to_window(a->mlx, a->win, gun_text[0], (a->win_x - gun_w)
		/ 4 * 3, a->win_y - gun_h);
	mlx_destroy_image(a->mlx, gun_text[0]);
}
