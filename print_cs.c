/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cCsS.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:51:53 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 15:51:54 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				print_s(va_list *l, t_printf f)
{
	char		*pr;
	int			length;

	pr = va_arg(*l, char *);
	if (f.pr < (int)ft_strlen1(pr) && f.pr >= 0)
		length = f.pr;
	else if (f.pr == -2)
		length = f.width;
	else
		length = ft_strlen1(pr);
	if (f.minus == 0)
		length += padding(f.width - length, f);
	if (f.pr >= 0)
		ft_putstrn(pr, f.pr);
	else if (f.pr == -2)
		padding(f.width, f);
	else
		ft_putstr(pr);
	if (f.minus == 1)
		length += padding(f.width - length, f);
	return (length);
}

int				ls_print(t_printf f, wchar_t *ws, int length)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	if (f.pr >= 0)
	{
		k += bits(ws[i]);
		while (ws[i] != '\0' && k <= f.pr)
		{
			to_unicode(ws[i++]);
			k += bits(ws[i]);
		}
	}
	else if (f.pr == -2)
	{
		padding(f.width, f);
		length = f.width;
	}
	else
		while (ws[i] != '\0')
			to_unicode(ws[i++]);
	length += (f.minus == 1) ? padding(f.width - length, f) : 0;
	return (length);
}

int				print_ls(va_list *l, t_printf f)
{
	wchar_t		*ws;
	int			length;
	int			i;
	int			k;

	i = 0;
	k = 0;
	length = 0;
	if (!(ws = va_arg(*l, wchar_t*)))
	{
		ft_putstr("(null)");
		return (6);
	}
	while (ws[i] != '\0')
		length += bits(ws[i++]);
	i = 0;
	if (f.pr < length && f.pr >= 0)
	{
		k += bits(ws[i]);
		while (ws[i++] != '\0' && k <= f.pr)
			k += bits(ws[i]);
		k -= bits(ws[i]);
		length = (f.pr > k) ? k : f.pr;
	}
	length += (f.minus == 0) ? padding(f.width - length, f) : 0;
	return (ls_print(f, ws, length));
}

int				print_c(va_list *l, t_printf f)
{
	int			length;
	char		ch;

	ch = (unsigned char)va_arg(*l, int);
	length = 1;
	if (f.minus == 0)
		length += padding(f.width - length, f);
	ft_putchar(ch);
	if (f.minus == 1)
		length += padding(f.width - length, f);
	return (length);
}

int				print_lc(va_list *l, t_printf f)
{
	int			length;
	wchar_t		wc;

	wc = (wchar_t)va_arg(*l, wint_t);
	length = bits(wc);
	if (f.minus == 0)
		length += padding(f.width - length, f);
	to_unicode(wc);
	if (f.minus == 1)
		length += padding(f.width - length, f);
	return (length);
}
