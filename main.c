#include "ft_printf.h"

int count_digits(intmax_t n)
{
	int			size;
	intmax_t	i;

	size = 1;
	i = 1;
	while (n / i > 0)
	{
		size++;
		i *= 10;
	}
	size--;
	return (size);
}

int	ft_printf(const char *s, ...)
{
	t_print	p;
	t_printf f;
	int i;
	char *pr;
	char *str;
	char ch;
	intmax_t n;
	uintmax_t un;
	wchar_t wc;
	wchar_t *ws;
	int k;
	int l;
	int q;
	int r;
	int g;

	i = 0;
	k = 0;
	l = 0;
	str = (char *)s;
	va_start(p.args, s);
	// f.flag = '\n';
	 f.min_width = 0;
	 f.presicion = 0;
	// f.length ='\n';
	// f.conversion = '\n';
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == '\0')
				break;
			if (ft_strchr("#0- + ", *str) != NULL)
			{
				f.flag = *str;
				str++;
			}
			// if (!ft_strchr(",;:_", *s))
			// {
			// 	f.separator = *s;
			// 	s++;
			// }
			if (*str >= 48 && *str <= 57)
			{
				f.min_width = ft_atoi(str);
				str = str + count_digits(f.min_width);
			}
			if (*str == '.')
			{
				str++;
				f.presicion = ft_atoi(str);
				str = str + count_digits(f.presicion);
			}
			if (*str == 'h' && *(str + 1) == 'h')
			{
				f.length = 's';
				str = str + 2;
			}
			else if (*str == 'l' && *(str + 1) == 'l')
			{
				f.length = 'w';
				str = str + 2;
			}
			else if (ft_strchr("hljz", *str) != NULL)
			{
				f.length = *str;
				str++;
			}
			if (ft_strchr("sSpdDioOuUxXcC%", *str) != NULL)
			{
				f.conversion = *str;
				str++;
			}
			// printf("%c\n", f.flag);
			// printf("%zu\n", f.min_width);
			// printf("%zu\n", f.presicion);
			// printf("%c\n", f.length);
			// printf("%c\n", f.conversion);
			if (f.conversion == '%')
			{
				ft_putchar('%');
				k++;
			}
			else if (f.conversion == 's')
			{
				pr = va_arg(p.args, char *);
				r = f.min_width - ft_strlen(pr);
				q = 0;
				while (q < r)
				{
					ft_putchar(' ');
					q++;
					k++;
				}
				ft_putstr(pr);
				k += ft_strlen(pr);
			}
			else if (f.conversion == 'S')
			{
				ws = va_arg(p.args, wchar_t*);
				l = 0;
				while (ws[l] != '\0')
				{
					pr = itoa_base(ws[l], 2, 0);
					to_unicode(pr);
					l++;
					k++;
				}
			}
			else if (f.conversion == 'C')
			{
				wc = (wchar_t)va_arg(p.args, wint_t);
				pr = itoa_base(wc, 2, 0);
				r = f.min_width - 1;
				q = 0;
				while (q < r)
				{
					ft_putchar(' ');
					q++;
					k++;
				}
				to_unicode(pr);
				k++;
			}
			else if (f.conversion == 'c')
			{
				// ch = va_arg(p.args, unsigned);
				r = f.min_width - 1;
				q = 0;
				while (q < r)
				{
					ft_putchar(' ');
					q++;
					k++;
				}
				if (f.length == 'l')
				{
					n = va_arg(p.args, int);
					pr = itoa_base(n, 2, 0);
					to_unicode(pr);
				}
				else
					ch = va_arg(p.args, unsigned);
					ft_putchar(ch);
				k++;
			}
			else if (f.conversion == 'd' || f.conversion == 'i' || f.conversion == 'u' 
				|| f.conversion == 'U' || f.conversion == 'D')
			{
				n = va_arg(p.args, intmax_t);
				r = f.min_width - count_digits(n);
				q = 0;
				while (q < r)
				{
					ft_putchar(' ');
					q++;
					k++;
				}
				if (f.length == 'l' || f.conversion == 'D')
					g = ft_putnbr((long)n);
				else if (f.length == 'h')
					g = ft_putnbr((short)n);
				else if (f.length == 'j')
					g = ft_putnbr((intmax_t)n);
				else if (f.length == 's')
					g = ft_putnbr((signed char)n);
				else if (f.length == 'w')
					g = ft_putnbr((long long)n);
				else
				{
					g = ft_putnbr((int)n);
				}
				k += g;
			}
			else if (f.conversion == 'o' || f.conversion == 'O')
			{
				un = va_arg(p.args, uintmax_t);
				//tmp = pr;
				pr = itoa_base(un, 8, 0);
				//free(tmp);
				r = f.min_width - ft_strlen(pr);
				q = 0;
				while (q < r)
				{
					ft_putchar(' ');
					q++;
					k++;
				}
				if (f.flag == '#')
				{
					ft_putchar('0');
					k++;
				}
				ft_putstr(pr);
				k += ft_strlen(pr);
			}
			else if (f.conversion == 'x' || f.conversion == 'p')
			{
				un = va_arg(p.args, uintmax_t);
				//tmp = pr;
				pr = itoa_base(un, 16, 0);
				//free(tmp);
				r = f.min_width - ft_strlen(pr);
				q = 0;
				while (q < r)
				{
					ft_putchar(' ');
					q++;
					k++;
				}
				if (f.flag == '#' || f.conversion == 'p')
				{
					ft_putstr("0x");
					k = k + 2;
				}
				ft_putstr(pr);
				k += ft_strlen(pr);
			}
			else if (f.conversion == 'X')
			{
				un = va_arg(p.args, uintmax_t);
				//tmp = pr;
				pr = itoa_base(un, 16, 1);
				//free(tmp);
				r = f.min_width - ft_strlen(pr);
				q = 0;
				while (q < r)
				{
					ft_putchar(' ');
					q++;
					k++;
				}
				if (f.flag == '#')
				{
					ft_putstr("0X");
					k = k + 2;
				}
				ft_putstr(pr);
				k += ft_strlen(pr);
			}

			//f = find(str);
			f.min_width = 0;
	 		f.presicion = 0;
			f.flag = '*';
			f.length = '*';
			f.conversion = '*';
		}
		else
		{
			ft_putchar(*str);
			str++;
			i++;
			k++;
		}
	}
	va_end(p.args);
	return (k);
}

// int	ft_printf(const char *s, ...)
// {
// 	t_print	p;
// 	t_printf f;
// 	int i;
// 	char *pr;
// 	//char *tmp;
// 	char ch;
// 	int n;
// 	int k;
// 	int l;

// 	i = 0;
// 	k = 0;
// 	l = 0;
// 	p.str = (char *)s;
// 	va_start(p.args, s);
// 	while (p.str[i])
// 	{
// 		if (p.str[i] == '%')
// 		{
// 			f = find()
// 			// i++;
// 			// if (p.str[i] == '%')
// 			// {
// 			// 	ft_putchar('%');
// 			// 	k++;
// 			// }
// 			// else if (p.str[i] == 's')
// 			// {
// 			// 	pr = va_arg(p.args, char *);
// 			// 	ft_putstr(pr);
// 			// 	k += ft_strlen(pr);
// 			// }
// 			// else if (p.str[i] == 'S')
// 			// {
// 			// 	pr = va_arg(p.args, char *);
// 			// 	while (pr[l] != '\0')
// 			// 	{
// 			// 		pr[l] = *itoa_base(n, 2, 0);
// 			// 		to_unicode(&pr[l]);
// 			// 		l++;
// 			// 	}
// 			// }
// 			// else if (p.str[i] == 'C')
// 			// {
// 			// 	n = va_arg(p.args, int);
// 			// 	pr = itoa_base(n, 2, 0);
// 			// 	to_unicode(pr);
// 			// 	k++;
// 			// }
// 			// else if (p.str[i] == 'c')
// 			// {
// 			// 	ch = va_arg(p.args, unsigned);
// 			// 	ft_putchar(ch);
// 			// 	k++;
// 			// }
// 			// else if (p.str[i] == 'd' || p.str[i] == 'i' || p.str[i] == 'u' || p.str[i] == 'U' || p.str[i] == 'D')
// 			// {
// 			// 	n = va_arg(p.args, int);
// 			// 	//ft_putnbr(n);
// 			// 	k += ft_putnbr(n);
// 			// }
// 			// else if (p.str[i] == 'o' || p.str[i] == 'O')
// 			// {
// 			// 	n = va_arg(p.args, int);
// 			// 	//tmp = pr;
// 			// 	pr = itoa_base(n, 8, 0);
// 			// 	//free(tmp);
// 			// 	ft_putstr(pr);
// 			// 	k += ft_strlen(pr);
// 			// }
// 			// else if (p.str[i] == 'x' || p.str[i] == 'p')
// 			// {
// 			// 	n = va_arg(p.args, int);
// 			// 	//tmp = pr;
// 			// 	pr = itoa_base(n, 16, 0);
// 			// 	//free(tmp);
// 			// 	ft_putstr(pr);
// 			// 	k += ft_strlen(pr);
// 			// }
// 			// else if (p.str[i] == 'X')
// 			// {
// 			// 	n = va_arg(p.args, int);
// 			// 	//tmp = pr;
// 			// 	pr = itoa_base(n, 16, 1);
// 			// 	//free(tmp);
// 			// 	ft_putstr(pr);
// 			// 	k += ft_strlen(pr);
// 			// }
// 			// else if (p.str[i] == '#')
// 			// {
// 			// 	i++;
// 			// 	if (p.str[i] == 'x')
// 			// 	{
// 			// 		n = va_arg(p.args, int);
// 			// 		//tmp = pr;
// 			// 		pr = itoa_base(n, 16, 0);
// 			// 		//free(tmp);
// 			// 		ft_putstr("0x");
// 			// 		ft_putstr(pr);
// 			// 		k += ft_strlen(pr) + 2;
// 			// 	}
// 			// 	else if (p.str[i] == 'X')
// 			// 	{
// 			// 		n = va_arg(p.args, int);
// 			// 		//tmp = pr;
// 			// 		pr = itoa_base(n, 16, 1);
// 			// 		//free(tmp);
// 			// 		ft_putstr("0X");
// 			// 		ft_putstr(pr);
// 			// 		k += ft_strlen(pr) + 2;
// 			// 	}
// 			// 	else if (p.str[i] == 'o' || p.str[i] == 'O')
// 			// 	{
// 			// 		n = va_arg(p.args, int);
// 			// 		//tmp = pr;
// 			// 		pr = itoa_base(n, 8, 0);
// 			// 		//free(tmp);
// 			// 		ft_putchar('0');
// 			// 		ft_putstr(pr);
// 			// 		k += ft_strlen(pr) + 1;
// 			// 	}
// 			// }
// 			// i++;
// 		}
// 		else
// 		{
// 			ft_putchar(p.str[i]);
// 			i++;
// 			k++;
// 		}
// 	}
// 	va_end(p.args);
// 	return (k);
// }
