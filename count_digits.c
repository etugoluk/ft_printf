/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:42:54 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 13:42:54 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

static int	spaces(const char *str)
{
	int		i;

	i = 0;
	while (str[i] == '\n' || str[i] == '\t' ||
		str[i] == '\r' || str[i] == '\v' ||
		str[i] == '\f' || str[i] == ' ')
		i++;
	return (i);
}

int			ft_atoi(char *str)
{
	int					i;
	unsigned long long	result;
	int					k;

	k = 1;
	i = 0;
	i = spaces(str);
	result = 0;
	if (((str[i] < 48) || (str[i] > 57)))
		return (-2);
	if (str[i] == '-')
		k = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		result = result * 10 + (int)(str[i++] - 48);
		if (result > 9223372036854775807 && k == 1)
			return (-1);
		else if (result > 9223372036854775807 && k == -1)
			return (0);
	}
	return ((int)result * k);
}

int				digits(intmax_t n, int k)
{
	int			size;
	intmax_t	i;

	size = 1;
	i = 1;
	if (n / 10 == -922337203685477580 && n % 10 == -8 && k == 0)
		return (20);
	else if (n / 10 == -922337203685477580 && n % 10 == -8 && k == 1)
		return (19);
	if (n < 0 && k == 0)
	{
		size++;
		n = -n;
	}
	else if (n < 0)
		n = -n;
	if (n == 0)
		return (1);
	while (n / i > 0)
	{
		size++;
		i *= 10;
	}
	size--;
	return (size);
}

int				digitsu(uintmax_t n)
{
	int			size;
	uintmax_t	i;

	size = 1;
	i = 1;
	if (n / 10 >= 1000000000000000000)
		return (20);
	if (n == 0)
		return (1);
	while (n / i > 0)
	{
		size++;
		i *= 10;
	}
	size--;
	return (size);
}
