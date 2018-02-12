#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
#include <stdlib.h>

typedef struct	s_print
{
	char		*str;
	va_list		args;
}				t_print;

int pow_function(int n, int pow);
char mod(int n, int k);
char *itoa_base(int n, int base, int k);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
int		ft_putnbr(int n);
size_t	ft_strlen(const char *s);
int		ft_printf(const char *s, ...);

#endif