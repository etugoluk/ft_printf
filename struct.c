/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:42:32 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 13:42:33 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			zero_struct(t_printf *f)
{
	(*f).plus = 0;
	(*f).minus = 0;
	(*f).space = 0;
	(*f).sharp = 0;
	(*f).zero = 0;
	(*f).width = 0;
	(*f).pr = -1;
	(*f).length = 0;
	(*f).c = 0;
}

void			write_flags(t_printf *f, char c)
{
	if (c == '+')
		(*f).plus = 1;
	else if (c == '-')
		(*f).minus = 1;
	else if (c == ' ')
		(*f).space = 1;
	else if (c == '#')
		(*f).sharp = 1;
	else if (c == '0')
		(*f).zero = 1;
}

void			f_length(const char **s, char *length)
{
	if (**s == 'h' && *(*s + 1) == 'h')
	{
		*length = 's';
		*s += 2;
	}
	else if (**s == 'l' && *(*s + 1) == 'l')
	{
		*length = 'w';
		*s += 2;
	}
	else if (ft_strchr("hljz", **s))
		*length = *(*s)++;
}

t_printf		fill_struct(const char **s)
{
	t_printf	f;

	zero_struct(&f);
	while (**s != '\0' && ft_strchr("#0-+ ", **s) != NULL)
		write_flags(&f, *(*s)++);
	if (**s == '\0')
		return (f);
	if (**s >= 48 && **s <= 57)
	{
		f.width = ft_atoi((char *)*s);
		*s += digits(f.width, 0);
	}
	if (**s == '.')
	{
		(*s)++;
		f.pr = ft_atoi((char *)*s);
		if (f.pr != -1 && f.pr != -2)
			*s += digits(f.pr, 0);
	}
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
