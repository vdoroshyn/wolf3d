/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:32:09 by vdoroshy          #+#    #+#             */
/*   Updated: 2016/12/06 13:09:22 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	int	i;

	if (s == NULL)
	{
		return ;
	}
	i = 0;
	while (*(s + i) != '\0')
	{
		ft_putchar(*(s + i));
		i++;
	}
}