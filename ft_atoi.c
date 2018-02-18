/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:14:31 by etugoluk          #+#    #+#             */
/*   Updated: 2017/10/30 14:14:35 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
