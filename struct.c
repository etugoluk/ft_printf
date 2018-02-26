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

void			f_flags(t_printf *f, char c)
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

void		f_width(const char **s, va_list *l, t_printf *f)
{
	if ((**s >= 48 && **s <= 57) || (**s == '*'))
	{
		(*f).width = (**s != '*') ? ft_atoi((char *)*s) : va_arg(*l, int);
		if ((*f).width < 0)
		{
			(*f).minus = 1;
			(*f).width *= -1;
		}
		*s += (**s != '*') ? digits((*f).width, 0) : 1;
	}
}

void		f_pr(const char **s, va_list *l, t_printf *f)
{
	if (**s == '.')
	{
		(*s)++;
		if (**s != '*')
		{
			(*f).pr = ft_atoi((char *)*s);
			if ((*f).pr != -1 && (*f).pr != -2)
				*s = *s + digits((*f).pr, 0);
		}
		else
		{
			(*f).pr = va_arg(*l, int);
			if ((*f).pr < 0)
				(*f).pr = -1;
			*s += 1;
		}
	}
}
