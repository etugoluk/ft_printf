#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
#include <stdlib.h>
#include <wchar.h>

typedef struct	s_print
{
	char		*str;
	va_list		args;
}				t_print;

typedef struct	s_printf
{
	//char		flag;
	char		plus;
	char		minus;
	char		space;
	char		sharp;
	char		zero;
	int			min_width;
	int			presicion;
	char 		length;
	char 		conversion;
}				t_printf;

int			ft_atoi(char *str);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
//int bits(int n);
//int to_char(char *s);
//int to_unicode(char *s);
int bits(wchar_t chr);
void to_unicode(wchar_t wc);
uintmax_t pow_function(uintmax_t n, int pow);
char mod(uintmax_t n, int k);
int check(int base);
char *itoa_base(uintmax_t n, int base, int k);
void	ft_putchar(char c);
int	ft_putstr(char const *s);
int		ft_putnbr(intmax_t n);
size_t	ft_strlen(const char *s);
int		ft_printf(const char *s, ...);
int	ft_putnbr1(uintmax_t n);
t_printf fill_struct(const char **s);
int write_struct(t_printf f, va_list *l);
int count_digits(intmax_t n, int k);
int print_procent(t_printf f);
int print_c(va_list *l, t_printf f);
int print_C(va_list *l, t_printf f);
int print_s(va_list *l, t_printf f);
int print_S(va_list *l, t_printf f);
int print_di(va_list *l, t_printf f);
int print_pxX(va_list *l, t_printf f);
int print_xX(va_list *l, t_printf f);
int print_D(va_list *l, t_printf f);
int print_O(va_list *l, t_printf f);
//int print_o(va_list *l, t_printf f);
int print_U(va_list *l, t_printf f);
int print_u(va_list *l, t_printf f);
char *right_pr(t_printf f, uintmax_t un);
void zero_struct(t_printf *f);
int right_padding(int r, t_printf f);
uintmax_t length_OU(va_list *l, t_printf f);
int	ft_putstrn(char const *s, int n);
intmax_t integer(va_list *l, t_printf f);
int count_digitsu(uintmax_t n);
size_t	ft_strlen1(const char *s);
#endif