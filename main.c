/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:18:03 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 13:18:05 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *s, ...)
{
	int			length;
	t_printf	f;
	va_list		l;

	length = 0;
	va_start(l, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			f = fill_struct(&s);
			length += write_struct(f, &l);
		}
		else
		{
			ft_putchar(*s);
			s++;
			length++;
		}
	}
	va_end(l);
	return (length);
}
