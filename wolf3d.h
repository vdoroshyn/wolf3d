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
	
}					t_all;

void				construct(t_all *a);
void				destruct(t_all *a);
void				proper_exit(t_all *a);
int					mouse_exit(void);

void				move(t_all *a, int keycode);

#endif
