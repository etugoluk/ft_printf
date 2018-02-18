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
	char		flag;
	//char		separator;
	int			min_width;
	size_t		presicion;
	char 		length;
	char 		conversion;
}				t_printf;

int			ft_atoi(char *str);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
int bits(int n);
int to_char(char *s);
void to_unicode(char *s);
uintmax_t pow_function(uintmax_t n, int pow);
char mod(uintmax_t n, int k);
char *itoa_base(uintmax_t n, int base, int k);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
int		ft_putnbr(intmax_t n);
size_t	ft_strlen(const char *s);
int		ft_printf(const char *s, ...);

#endif