/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:39:49 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 15:39:50 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>

typedef struct	s_printf
{
	char		plus;
	char		minus;
	char		space;
	char		sharp;
	char		zero;
	int			width;
	int			pr;
	char		length;
	char		c;
}				t_printf;

int				ft_printf(const char *s, ...);
t_printf		fill_struct(const char **s, va_list *l);
int				write_struct(t_printf f, va_list *l);
void			zero_struct(t_printf *f);
void			f_flags(t_printf *f, char c);
void			f_length(const char **s, char *length);
void			f_width(const char **s, va_list *l, t_printf *f);
void			f_pr(const char **s, va_list *l, t_printf *f);
int				print_di(va_list *l, t_printf f);
int				print_s(va_list *l, t_printf f);
int				print_ls(va_list *l, t_printf f);
int				print_c(va_list *l, t_printf f);
int				print_lc(va_list *l, t_printf f);
int				print_o(va_list *l, t_printf f);
int				print_u(va_list *l, t_printf f);
int				print_px(va_list *l, t_printf f);
int				print_procent(t_printf f, char c);
int				bits(wchar_t chr);
void			to_unicode(wchar_t chr);
char			*ft_strchr(const char *s, int c);
int				ft_atoi(char *str);
int				digits(intmax_t n, int k);
int				digitsu(uintmax_t n);
void			ft_putchar(char c);
int				ft_putstr(char const *s);
int				ft_putstrn(char const *s, int n);
void			ft_putnbr(intmax_t n);
void			ft_putnbr1(uintmax_t n);
char			*itoa_base(uintmax_t n, int base, int k);
size_t			len(const char *s);
int				padding(int r, t_printf f);
int				presicions(int n);

#endif
