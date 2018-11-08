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

t_printf		fill_struct(const char **s, va_list *l)
{
	t_printf	f;

	zero_struct(&f);
	while (**s != '\0' && ft_strchr("#0-+ ", **s) != NULL)
		f_flags(&f, *(*s)++);
	if (**s == '\0')
		return (f);
	f_width(s, l, &f);
	f_width(s, l, &f);
	f_pr(s, l, &f);
	f_length(s, &f.length);
	if (**s != '\0')
		f.c = *(*s)++;
	return (f);
}

int				write_struct(t_printf f, va_list *l)
{
	if (f.c == 0)
		return (padding(f.width, f));
	if (ft_strchr("diD", f.c) != NULL)
		return (print_di(l, f));
	else if (f.c == 'O' || f.c == 'o')
		return (print_o(l, f));
	else if (f.c == 'U' || f.c == 'u')
		return (print_u(l, f));
	else if (f.c == 'x' || f.c == 'X' || f.c == 'p')
		return (print_px(l, f));
	else if (f.c == 'S' || (f.c == 's' && f.length == 'l'))
		return (print_ls(l, f));
	else if (f.c == 's')
		return (print_s(l, f));
	else if (f.c == 'C' || (f.c == 'c' && f.length == 'l'))
		return (print_lc(l, f));
	else if (f.c == 'c')
		return (print_c(l, f));
	else
		return (print_procent(f, f.c));
	return (0);
}

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
			f = fill_struct(&s, &l);
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
