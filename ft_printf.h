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
# include <stdio.h>
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

int				ft_atoi(char *str);
char			*ft_strchr(const char *s, int c);
int				bits(wchar_t chr);
void			to_unicode(wchar_t wc);
uintmax_t		pow_function(uintmax_t n, int pow);
char			mod(uintmax_t n, int k);
int				check(int base);
char			*itoa_base(uintmax_t n, int base, int k);
void			ft_putchar(char c);
int				ft_putstr(char const *s);
void			ft_putnbr(intmax_t n);
size_t			ft_strlen(const char *s);
int				ft_printf(const char *s, ...);
void			ft_putnbr1(uintmax_t n);
t_printf		fill_struct(const char **s);
int				write_struct(t_printf f, va_list *l);
int				digits(intmax_t n, int k);
int				print_procent(t_printf f, char c);
int				print_c(va_list *l, t_printf f);
int				print_lc(va_list *l, t_printf f);
int				print_s(va_list *l, t_printf f);
int				print_ls(va_list *l, t_printf f);
int				print_di(va_list *l, t_printf f);
int				print_px(va_list *l, t_printf f);
int				print_o(va_list *l, t_printf f);
int				print_u(va_list *l, t_printf f);
char			*right_pr(t_printf f, uintmax_t un);
void			zero_struct(t_printf *f);
int				padding(int r, t_printf f);
uintmax_t		length_ou(va_list *l, t_printf f);
int				ft_putstrn(char const *s, int n);
intmax_t		integer(va_list *l, t_printf f);
int				digitsu(uintmax_t n);
size_t			ft_strlen1(const char *s);
void			f_length(const char **s, char *length);
int				presicions(int n);
#endif
