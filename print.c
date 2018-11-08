/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:18:12 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 13:18:13 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		len(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (6);
	while (s[i] != '\0')
		i++;
	return (i);
}

int			padding(int r, t_printf f)
{
	int		length;
	int		i;

	length = 0;
	i = 0;
	while (i < r)
	{
		if (f.zero == 1 && f.minus == 0 && f.pr < 0)
			ft_putchar('0');
		else
			ft_putchar(' ');
		i++;
		length++;
	}
	return (length);
}

int			print_procent(t_printf f, char c)
{
	int		length;

	length = 1;
	if (f.minus == 0)
		length += padding(f.width - length, f);
	ft_putchar(c);
	if (f.minus == 1)
		length += padding(f.width - length, f);
	return (length);
}

int			presicions(int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		ft_putchar('0');
		i++;
	}
	return (i);
}
