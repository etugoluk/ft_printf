/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:12:15 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 15:12:23 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t			integer(va_list *l, t_printf f)
{
	if (f.length == 'l')
		return (long)va_arg(*l, intmax_t);
	else if (f.length == 'h' && f.c != 'D')
		return (short)va_arg(*l, intmax_t);
	else if (f.length == 's' && f.c != 'D')
		return (signed char)va_arg(*l, intmax_t);
	else if (f.length == 'w')
		return (long long)va_arg(*l, intmax_t);
	else if (f.length == 'z')
		return (size_t)va_arg(*l, intmax_t);
	else if (f.length == 'j' || f.c == 'D')
		return (intmax_t)va_arg(*l, intmax_t);
	else
		return (int)va_arg(*l, intmax_t);
}

static int				di_flags(t_printf f, intmax_t n, int k)
{
	int			length;

	length = k;
	if (((f.plus == 1 && (n >= 0))) ||
		((f.space == 1 && f.minus == 0 && f.plus == 0 && (n >= 0))) ||
		(f.zero == 1 && (n < 0)) || (n < 0 && (f.pr <= digits(n, 1))))
		length++;
	if (f.zero == 1 && (n < 0))
		ft_putchar('-');
	if (f.plus == 1 && (n >= 0) && f.zero == 1)
		ft_putchar('+');
	else if (f.space == 1 && f.minus == 0 && f.plus == 0 && (n >= 0))
		ft_putchar(' ');
	if (f.minus == 0)
	{
		if (f.pr > digits(n, 1) && n >= 0)
			length += padding(f.width - length - (f.pr - digits(n, 1)), f);
		else if (f.pr > digits(n, 1) && n < 0)
			length += padding(f.width - length - (f.pr - digits(n, 1) + 1), f);
		else
			length += padding(f.width - length, f);
	}
	if (f.plus == 1 && (n >= 0) && f.zero == 0)
		ft_putchar('+');
	return (length);
}

int						print_di(va_list *l, t_printf f)
{
	int					length;
	intmax_t			n;

	n = integer(l, f);
	length = digits(n, 1);
	length = di_flags(f, n, length);
	if (f.pr > digits(n, 1) && (n < 0) && f.zero == 0)
	{
		ft_putchar('-');
		length++;
	}
	if (f.pr > digits(n, 1))
		length += presicions(f.pr - digits(n, 1));
	if ((f.zero == 1 && (n < 0)) || (f.pr > digits(n, 1) && (n < 0)))
		n = -n;
	if ((f.pr == 0 || f.pr == -2) && (n == 0))
		if (f.width > 0)
			ft_putchar(' ');
		else
			length--;
	else
		ft_putnbr(n);
	if (f.minus == 1)
		length += padding(f.width - length, f);
	return (length);
}
