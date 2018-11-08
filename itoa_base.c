/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:55:23 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 15:55:24 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	pow_function(uintmax_t n, int pow)
{
	uintmax_t		result;
	int				i;

	result = 1;
	i = 0;
	if (pow < 0)
		return (0);
	while (i++ < pow)
	{
		result *= n;
	}
	return (result);
}

static char			mod(uintmax_t n, int k)
{
	char			c;

	if (n <= 9)
		c = n + 48;
	else if (k == 0)
		c = n - 10 + 97;
	else if (k == 1)
		c = n - 10 + 65;
	else
		c = '\0';
	return (c);
}

static int			check(int base)
{
	if (base == 2)
		return (64);
	if (base == 8)
		return (22);
	if (base == 16)
		return (16);
	return (0);
}

char				*itoa_base(uintmax_t n, int base, int k)
{
	int				i;
	char			*number;

	i = 1;
	while (i < check(base) && pow_function(base, i) <= n)
		i++;
	number = (char *)malloc(sizeof(char) * (i + 1));
	number[i] = '\0';
	i--;
	while (i >= 0)
	{
		number[i] = mod(n % base, k);
		n = n / base;
		i--;
	}
	return (number);
}
