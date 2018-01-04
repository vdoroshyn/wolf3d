/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:35:52 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/03/28 16:36:20 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_abs(int x)
{
	if (x == -2147483648)
	{
		return (x);
	}
	if (x < 0)
	{
		return (x * -1);
	}
	return (x);
}
