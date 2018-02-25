/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_px.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:17:39 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 15:17:40 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*right_pr(t_printf f, uintmax_t un)
{
	int			k;

	k = (f.c == 'X') ? 1 : 0;
	if (f.c == 'p')
		return (itoa_base(un, 16, k));
	if (f.length == 'h')
		return (itoa_base((unsigned short)un, 16, k));
	if (f.length == 'l')
		return (itoa_base((unsigned long)un, 16, k));
	if (f.length == 'z')
		return (itoa_base((size_t)un, 16, k));
	if (f.length == 's')
		return (itoa_base((unsigned char)un, 16, k));
	if (f.length == 'j')
		return (itoa_base((uintmax_t)un, 16, k));
	if (f.length == 'w')
		return (itoa_base((unsigned long long)un, 16, k));
	else
		return (itoa_base((unsigned int)un, 16, k));
	return (NULL);
}

int				flags_px(t_printf f, char *pr, uintmax_t un)
{
	int			length;

	length = ft_strlen(pr); 
	length += ((f.sharp == 1 && un != 0) || (f.c == 'p')) ? 2 : 0;
	if ((f.zero == 1 && f.sharp == 1 && un != 0) ||
		(f.c == 'p' && f.zero == 1))
	{
		if (f.c == 'x' || (f.c == 'p'))
			ft_putstr("0x");
		if (f.c == 'X')
			ft_putstr("0X");
	}
	if (f.minus == 0)
		length += (f.pr > (int)ft_strlen(pr)) ? padding(f.width - length - (f.pr - ft_strlen(pr)), f) : padding(f.width - length, f);;
	if ((f.zero == 0 && f.sharp == 1 && un != 0) ||
		(f.c == 'p' && f.zero == 0))
	{
		if (f.c == 'x' || (f.c == 'p'))
			ft_putstr("0x");
		if (f.c == 'X')
			ft_putstr("0X");
	}
	length += (f.pr > (int)ft_strlen(pr)) ? presicions(f.pr - ft_strlen(pr)) : 0;
	return (length);
}

int				print_px(va_list *l, t_printf f)
{
	int			length;
	uintmax_t	un;
	char		*pr;

	un = va_arg(*l, uintmax_t);
	pr = right_pr(f, un);
	length = flags_px(f, pr, un);
	if ((f.pr == 0 || f.pr == -2) && (un == 0))
		if (f.width > 0)
			ft_putchar(' ');
		else
			length--;
	else
		ft_putstr(pr);
	length += (f.minus == 1) ? padding(f.width - length, f) : 0;
	free(pr);
	pr = NULL;
	return (length);
}
