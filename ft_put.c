/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:20:06 by etugoluk          #+#    #+#             */
/*   Updated: 2017/10/30 14:20:08 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}

int	ft_putnbr(int n)
{
	long	i;
	long	n_copy;
	long	div;
	int		k;

	k = 0;
	div = 0;
	i = 1;
	n_copy = n;
	if (n < 0)
	{
		ft_putchar('-');
		n_copy = -n_copy;
	}
	while ((n_copy / i) > 0)
		i *= 10;
	if (n_copy != 0)
		i /= 10;
	while (i != 0)
	{
		div = n_copy / i;
		ft_putchar(div + 48);
		n_copy %= i;
		i /= 10;
		k++;
	}
	return (k);
}
