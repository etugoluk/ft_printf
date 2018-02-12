#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	t_print	p;
	int i;
	char *pr;
	char *tmp;
	char ch;
	int n;
	int k;

	i = 0;
	k = 0;
	p.str = (char *)s;
	va_start(p.args, s);
	while (p.str[i])
	{
		if (p.str[i] == '%')
		{
			i++;
			if (p.str[i] == '%')
			{
				ft_putchar('%');
				k++;
			}
			else if (p.str[i] == 's' || p.str[i] == 'S')
			{
				pr = va_arg(p.args, char *);
				ft_putstr(pr);
				k += ft_strlen(pr);
			}
			else if (p.str[i] == 'c' || p.str[i] == 'C')
			{
				ch = va_arg(p.args, unsigned);
				ft_putchar(ch);
				k++;
			}
			else if (p.str[i] == 'd' || p.str[i] == 'i' || p.str[i] == 'u')
			{
				n = va_arg(p.args, int);
				//ft_putnbr(n);
				k += ft_putnbr(n);
			}
			else if (p.str[i] == 'o')
			{
				n = va_arg(p.args, int);
				tmp = pr;
				pr = itoa_base(n, 8, 0);
				free(tmp);
				ft_putstr(pr);
				k += ft_strlen(pr);
			}
			else if (p.str[i] == 'x')
			{
				n = va_arg(p.args, int);
				tmp = pr;
				pr = itoa_base(n, 16, 0);
				free(tmp);
				ft_putstr(pr);
				k += ft_strlen(pr);
			}
			else if (p.str[i] == 'X')
			{
				n = va_arg(p.args, int);
				tmp = pr;
				pr = itoa_base(n, 16, 1);
				free(tmp);
				ft_putstr(pr);
				k += ft_strlen(pr);
			}
			i++;
		}
		else
		{
			ft_putchar(p.str[i]);
			i++;
			k++;
		}
	}
	va_end(p.args);
	return (k);
}
