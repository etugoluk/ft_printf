/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oOuU.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:55:30 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 14:55:30 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	length_ou(va_list *l, t_printf f)
{
	if (f.c == 'U' || f.c == 'O')
		return (va_arg(*l, uintmax_t));
	if (f.length == 'l')
		return (unsigned long)va_arg(*l, uintmax_t);
	else if (f.length == 'h')
		return (unsigned short)va_arg(*l, uintmax_t);
	else if (f.length == 's')
		return (unsigned char)va_arg(*l, uintmax_t);
	else if (f.length == 'w')
		return (unsigned long long)va_arg(*l, uintmax_t);
	else if (f.length == 'j')
		return (uintmax_t)va_arg(*l, uintmax_t);
	else if (f.length == 'z')
		return (size_t)va_arg(*l, uintmax_t);
	return (unsigned int)va_arg(*l, uintmax_t);
}

int					print_o(va_list *l, t_printf f)
{
	uintmax_t		un;
	char			*pr;
	int				length;

	un = length_ou(l, f);
	pr = itoa_base(un, 8, 0);
	length = len(pr);
	if (f.sharp == 1 && un != 0 && f.pr < 0)
		length++;
	if (f.minus == 0)
		length += (f.pr > (int)len(pr)) ? padding(f.width
		- length - f.pr + len(pr), f) : padding(f.width - length, f);
	if (f.sharp == 1 && un != 0 && f.pr < 0)
		ft_putchar('0');
	length += (f.pr > digits(un, 1)) ? presicions(f.pr - len(pr)) : 0;
	if ((f.pr == 0 || f.pr == -2) && (un == 0) && (f.sharp == 0))
		if (f.width > 0)
			ft_putchar(' ');
		else
			length--;
	else
		ft_putstr(pr);
	length += (f.minus == 1) ? padding(f.width - length, f) : 0;
	free(pr);
	return (length);
}

int					print_u(va_list *l, t_printf f)
{
	int				length;
	uintmax_t		un;

	un = length_ou(l, f);
	length = digitsu(un);
	if (f.minus == 0)
	{
		if (f.pr > digits(un, 1))
			length += padding(f.width - length - (f.pr - digits(un, 1)), f);
		else
			length += padding(f.width - length, f);
	}
	if (f.pr > digits(un, 1))
		length += presicions(f.pr - digits(un, 1));
	if ((f.pr == 0 || f.pr == -2) && (un == 0))
		if (f.width > 0)
			ft_putchar(' ');
		else
			length--;
	else
		ft_putnbr1(un);
	if (f.minus == 1)
		length += padding(f.width - length, f);
	return (length);
}
