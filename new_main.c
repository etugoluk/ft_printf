#include "ft_printf.h"

int count_digits(intmax_t n, int k)
{
	int			size;
	intmax_t	i;

	size = 1;
	i = 1;
	if (n / 10 == -922337203685477580 && n % 10 == -8 && k == 0)
		return (20);
	else if (n / 10 == -922337203685477580 && n % 10 == -8  && k == 1)
		return (19);
	if (n < 0 && k == 0)
	{
		size++;
		n = -n;
	}
	else if (n < 0)
		n = -n;
	if (n == 0)
		return (1);
	while (n / i > 0)
	{
		size++;
		i *= 10;
	}
	size--;
	return (size);
}

int count_digitsu(uintmax_t n)
{
	int			size;
	uintmax_t	i;

	size = 1;
	i = 1;
	// if (n / 10 == -922337203685477580 && n % 10 == -8 && k == 0)
	// 	return (20);
	// else if (n / 10 == -922337203685477580 && n % 10 == -8  && k == 1)
	// 	return (19);

	if (n / 10 >= 1000000000000000000)
		return (20);
	if (n == 0)
		return (1);
	while (n / i > 0)
	{
		size++;
		i *= 10;
	}
	size--;
	return (size);
}

void zero_struct(t_printf *f)
{
	(*f).plus = 0;
	(*f).minus = 0;
	(*f).space = 0;
	(*f).sharp = 0;
	(*f).zero = 0;	
	//(*f).flag = 0;
	(*f).min_width = 0;
	(*f).presicion = -1;
	(*f).length = 0;
	(*f).conversion = 0;
}

void write_flags(t_printf *f, char c)
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

t_printf fill_struct(const char **s)
{
	t_printf f;

	zero_struct(&f);
	if (**s == '\0')
		return (f);
	while (**s != '\0' && ft_strchr("#0- + ", **s) != NULL)
	{
		write_flags(&f, **s);
		(*s)++;
	}
	if (**s == '\0')
		return (f);
	if (**s >= 48 && **s <= 57)
	{
		f.min_width = ft_atoi((char *)*s);
		*s = *s + count_digits(f.min_width, 0);
	}
	if (**s == '.')
	{
		(*s)++;
		f.presicion = ft_atoi((char *)*s);
		if (f.presicion != -1 && f.presicion != -2)
			*s = *s + count_digits(f.presicion, 0);
	}
	if (**s == 'h' && *(*s + 1) == 'h')
	{
		f.length = 's';
		*s = *s + 2;
	}
	else if (**s == 'l' && *(*s + 1) == 'l')
	{
		f.length = 'w';
		*s = *s + 2;
	}
	else if (ft_strchr("hljz", **s))
	{
		f.length = **s;
		(*s)++;
	}
	if (**s != '\0')
	{
		f.conversion = **s;
		(*s)++;
	}
	return (f);
}

int write_struct(t_printf f, va_list *l)
{
	int length;

	length = 0;
	if (f.conversion == 0)
	{
		length += right_padding(f.min_width, f);
		return (length);
	}
	else if (f.conversion == '%')	
		length += print_procent(f);
	else if (ft_strchr("di", f.conversion) != NULL)
		length += print_di(l, f);
	else if (f.conversion == 'D')
		length += print_D(l, f);
	else if (f.conversion == 'O')
		length += print_O(l, f);
	else if (f.conversion == 'o')
		length += print_O(l, f);
	else if (f.conversion == 'U')
		length += print_U(l, f);
	else if (f.conversion == 'u')
		length += print_u(l, f);
	else if (f.conversion == 'x' || f.conversion == 'X')
		length += print_xX(l, f);
	else if (f.conversion == 'p')
		length += print_xX(l, f);
	else if (f.conversion == 'S' || (f.conversion == 's' && f.length == 'l'))
		length += print_S(l, f);
	else if (f.conversion == 's')
		length += print_s(l, f);
	else if (f.conversion == 'C' || (f.conversion == 'c' && f.length == 'l'))
		length += print_C(l, f);
	else if (f.conversion == 'c')
		length += print_c(l, f);
	else
	{
		if (f.minus == 0)
			length += right_padding(f.min_width - 1, f);
		ft_putchar(f.conversion);
		length++;
		if (f.minus == 1)
			length += right_padding(f.min_width - 1, f);
	}
	return (length);
}

int	ft_printf(const char *s, ...)
{
	int length;
	t_printf f;
	va_list l;

	length = 0;
	va_start(l, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			f = fill_struct(&s);
			length += write_struct(f, &l);
		}
		else
		{
			ft_putchar(*s);
			s++;
			length++;
		}
	}
	va_end(l);
	return (length);
}