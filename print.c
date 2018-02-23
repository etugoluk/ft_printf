#include "ft_printf.h"

int right_padding(int r, t_printf f)
{
	int length;
	int i;

	length = 0;
	i = 0;
	while (i < r)
	{
		if (f.zero == 1 && f.minus == 0 && f.presicion < 0)
			ft_putchar('0');
		else
			ft_putchar(' ');
		i++;
		length++;
	}
	return (length);
}

int print_procent(t_printf f)
{
	int length;

	length = 1;
	if (f.minus == 0)
		length += right_padding(f.min_width - length, f);
	ft_putchar('%');
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

int print_s(va_list *l, t_printf f)
{
	char *pr;
	int length;

	length = 0;
	pr = va_arg(*l, char *);
	if (f.minus == 0)
	{
		if (f.presicion < (int)ft_strlen(pr) && f.presicion != -1)
			length += right_padding(f.min_width - f.presicion, f);
		else
			length += right_padding(f.min_width - ft_strlen(pr), f);
	}
	if (f.presicion != -1)
		length += ft_putstrn(pr, f.presicion);
	else
		length += ft_putstr(pr);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

int print_S(va_list *l, int width)
{
	wchar_t *ws;
	char *pr;
	//char *tmp;
	int length;
	int i;

	i = 0;
	length = 0;
	width = 0;
	ws = va_arg(*l, wchar_t*);
	if (!ws)
	{
		ft_putstr("(null)");
		length += 6;
	}
	else
		while (ws[i] != '\0')
		{
			//tmp = pr;
			pr = itoa_base(ws[i], 2, 0);
			length += to_unicode(pr);
			//free (tmp);
			i++;
		}
	return (length);
}

int print_c(va_list *l, t_printf f)
{
	int length;
	char ch;
	char *pr;
	int q;

	length = 0;
	if (f.minus == 0)
		length += right_padding(f.min_width - 1, f);
	if (f.length == 'l')
	{
		q = va_arg(*l, int);
		pr = itoa_base(q, 2, 0);
		length += to_unicode(pr);
	}
	else
	{
		ch = (unsigned char)va_arg(*l, int);
		ft_putchar(ch);
		length++;
	}
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

int print_C(va_list *l, t_printf f)
{
	int length;
	wchar_t wc;
	char *pr;

	length = 0;
	if (f.minus == 0)
		length += right_padding(f.min_width - 1, f);
	wc = (wchar_t)va_arg(*l, wint_t);
	pr = itoa_base(wc, 2, 0);
	length += to_unicode(pr);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

intmax_t integer(va_list *l, t_printf f)
{
	if (f.length == 'l')
		return (long)va_arg(*l, intmax_t);
	else if (f.length == 'h')
		return (short)va_arg(*l, intmax_t);
	else if (f.length == 's')
		return (signed char)va_arg(*l, intmax_t);
	else if (f.length == 'w')
		return (long long)va_arg(*l, intmax_t);
	else if (f.length == 'z')
		return (size_t)va_arg(*l, intmax_t);
	else if (f.length == 'j')
		return (intmax_t)va_arg(*l, intmax_t);
	else
		return (int)va_arg(*l, intmax_t);
}

int presicions(int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putchar('0');
		i++;
	}
	return (i);
}

int print_di(va_list *l, t_printf f)
{
	int length;
	intmax_t n;

	n = integer(l, f);
	length = count_digits((long long)n, 1);
	if (((f.plus == 1 && (n >= 0))) || 
		((f.space == 1 && f.minus == 0 && f.plus == 0 && ((int)n >= 0))))
		length++;
	if (f.zero == 1 && (n < 0))
	{
		ft_putchar('-');
		length++;
	}
	else if (n < 0 && (f.presicion <= count_digits((long long)n, 1)))
		length++;
	if (f.plus == 1 && (n >= 0) && f.zero == 1)
		ft_putchar('+');
	else if (f.space == 1 && f.minus == 0 && f.plus == 0 && ((int)n >= 0))
		ft_putchar(' ');
	if (f.minus == 0)
	{
		if (f.presicion > count_digits((long long)n, 1) && n >= 0)
			length += right_padding(f.min_width - length - (f.presicion - count_digits((long long)n, 1)), f);
		else if (f.presicion > count_digits((long long)n, 1) && n < 0)
			length += right_padding(f.min_width - length - (f.presicion - count_digits((long long)n, 1) + 1), f);
		else
		{
			length += right_padding(f.min_width - length, f);
		}
	}
	if (f.plus == 1 && (n >= 0) && f.zero == 0)
		ft_putchar('+');
	if (f.presicion > count_digits((long long)n, 1) && (n < 0) && f.zero == 0)
	{
		ft_putchar('-');
		length++;
	}
	if (f.presicion > count_digits((long long)n, 1))
		length += presicions(f.presicion - count_digits((long long)n, 1));
	if ((f.zero == 1 && (n < 0)) || (f.presicion > count_digits((long long)n, 1) && (n < 0)))
		n = -n;
	if ((f.presicion == 0 || f.presicion == -2) && (n == 0))
	{
		ft_putchar(' ');
	}
	else
		ft_putnbr(n);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

int print_D(va_list *l, t_printf f)
{
	int length;
	intmax_t n;

	length = 0;
	n = va_arg(*l, intmax_t);
	if (f.minus == 0)
		length += right_padding(f.min_width - count_digits(n, 0), f);
	length += ft_putnbr(n);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

uintmax_t length_OU(va_list *l, t_printf f)
{
	if (f.conversion == 'U' || f.conversion == 'O')
		return va_arg(*l, uintmax_t);
	if (f.length == 'l')
		return (unsigned long)va_arg(*l, uintmax_t);
	else if (f.length == 'h')
		return (unsigned short)va_arg(*l, uintmax_t);
	else if (f.length == 's')
		return (unsigned char)va_arg(*l, uintmax_t);
	else if (f.length == 'w')
		return (unsigned long long)va_arg(*l, uintmax_t);
	else if (f.length == 'j')
		return (uintmax_t)va_arg(*l, uintmax_t);
	else if (f.length == 'z')
		return (size_t)va_arg(*l, uintmax_t);
	return (unsigned int)va_arg(*l, uintmax_t);
}

// int print_O(va_list *l, t_printf f)
// {
// 	uintmax_t un;
// 	char *pr;
// 	int length;

// 	length = 0;
// 	un = length_OU(l, f);
// 	pr = itoa_base(un, 8, 0);
// 	if (f.minus == 0 && f.sharp == 0)
// 		length += right_padding(f.min_width - ft_strlen(pr), f);
// 	if (f.sharp == 1 && un != 0)
// 	{
// 		if (f.minus == 0)
// 			length += right_padding(f.min_width - ft_strlen(pr) - 1, f);
// 		ft_putchar('0');
// 		length++;
// 	}
// 	ft_putstr(pr);
// 	length += ft_strlen(pr);
// 	if (f.minus == 1)
// 		length += right_padding(f.min_width - length, f);
// 	return (length);
// }

int print_O(va_list *l, t_printf f)
{
	uintmax_t un;
	char *pr;
	int length;

	un = length_OU(l, f);
	pr = itoa_base(un, 8, 0);
	length = ft_strlen(pr);
	if (f.minus == 0 && f.sharp == 0)
	{
		if (f.presicion > (int)ft_strlen(pr))
				length += right_padding(f.min_width - length - (f.presicion - ft_strlen(pr)), f);
		else
				length += right_padding(f.min_width - length, f);
	}
	if (f.sharp == 1 && un != 0)
	{
		length++;
		if (f.minus == 0)
		{
			if (f.presicion > (int)ft_strlen(pr))
				length += right_padding(f.min_width - length - (f.presicion - ft_strlen(pr)), f);
			else
				length += right_padding(f.min_width - length, f);
		}
		ft_putchar('0');
	}
	if (f.presicion > count_digits(un, 1))
		length += presicions(f.presicion - ft_strlen(pr));
	if ((f.presicion == 0 || f.presicion == -2) && (un == 0))
	{
		length -= ft_strlen(pr);
	}
	else
		ft_putstr(pr);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

int print_U(va_list *l, t_printf f)
{
	int length;
	uintmax_t un;

	length = 0;
	un = length_OU(l, f);
	if (f.minus == 0)
		length += right_padding(f.min_width - count_digits(un, 0), f);
	length += ft_putnbr1(un);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

int print_u(va_list *l, t_printf f)
{
	int length;
	uintmax_t un;

	un = length_OU(l, f);
	length = count_digitsu(un);
	if (f.minus == 0)
	{
		if (f.presicion > count_digits(un, 1))
			length += right_padding(f.min_width - length - (f.presicion - count_digits(un, 1)), f);
		else
			length += right_padding(f.min_width - length, f);
	}
	if (f.presicion > count_digits(un, 1))
		length += presicions(f.presicion - count_digits(un, 1));
	if ((f.presicion == 0 || f.presicion == -2) && (un == 0))
		length--;
	else
		ft_putnbr1(un);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

char *right_pr(t_printf f, uintmax_t un)
{
	if (f.conversion == 'p')
		return (itoa_base(un, 16, 0));
	if (f.conversion == 'x')
	{
		if (f.length == 'h')
			return (itoa_base((unsigned short)un, 16, 0));
		if (f.length == 'l')
			return (itoa_base((unsigned long)un, 16, 0));
		if (f.length == 'z')
			return (itoa_base((size_t)un, 16, 0));
		if (f.length == 's')
			return (itoa_base((unsigned char)un, 16, 0));
		if (f.length == 'j')
			return (itoa_base((uintmax_t)un, 16, 0));
		if (f.length == 'w')
			return (itoa_base((unsigned long long)un, 16, 0));
		else
			return (itoa_base((unsigned int)un, 16, 0));
	}
	if (f.conversion == 'X')
	{
		if (f.length == 'h')
			return (itoa_base((unsigned short)un, 16, 1));
		if (f.length == 'l')
			return (itoa_base((unsigned long)un, 16, 1));
		if (f.length == 'z')
			return (itoa_base((size_t)un, 16, 1));
		if (f.length == 's')
			return (itoa_base((unsigned char)un, 16, 1));
		if (f.length == 'j')
			return (itoa_base((uintmax_t)un, 16, 1));
		if (f.length == 'w')
			return (itoa_base((unsigned long long)un, 16, 1));
		else
			return (itoa_base((unsigned int)un, 16, 1));
	}
	return (NULL);
}

int print_pxX(va_list *l, t_printf f)
{
	int length;
	uintmax_t un;
	char *pr;

	length = 0;
	un = va_arg(*l, uintmax_t);
	pr = right_pr(f, un);
	if (f.zero == 1)
	{
		if ((f.sharp == 1 && f.conversion == 'x' && un != 0) || (f.conversion == 'p')) 
		{
			ft_putstr("0x");
			length += 2;
		}
		if (f.sharp == 1 && f.conversion == 'X' && un != 0)
		{
			ft_putstr("0X");
			length += 2;
		}
	}
	if (((f.sharp == 1 && f.conversion == 'x') || f.conversion == 'p' || (f.sharp == 1 && f.conversion == 'X')) && (f.minus == 0))
		length += right_padding(f.min_width - ft_strlen(pr) - 2, f);
	else if (f.minus == 0)
		length += right_padding(f.min_width - ft_strlen(pr), f);
	if (f.zero == 0)
	{
		if ((f.sharp == 1 && f.conversion == 'x' && un != 0) || (f.conversion == 'p')) 
		{
			ft_putstr("0x");
			length += 2;
		}
		if (f.sharp == 1 && f.conversion == 'X' && un != 0)
		{
			ft_putstr("0X");
			length += 2;
		}
	}
	ft_putstr(pr);
	length +=ft_strlen(pr);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}


int print_xX(va_list *l, t_printf f)
{
	int length;
	uintmax_t un;
	char *pr;

	un = va_arg(*l, uintmax_t);
	pr = right_pr(f, un);
	length = ft_strlen(pr);
	if ((f.sharp == 1 && un != 0) || (f.conversion == 'p'))
		length += 2;
	if (f.zero == 1 && f.sharp == 1 && un != 0)
	{	
		if (f.conversion == 'x')
			ft_putstr("0x");
		if (f.conversion == 'X')
			ft_putstr("0X");
	}
	if (f.minus == 0)
	{
		if (f.presicion > (int)ft_strlen(pr))
			length += right_padding(f.min_width - length - (f.presicion - ft_strlen(pr)), f);
		else
			length += right_padding(f.min_width - length, f);
	}
	if ((f.zero == 0 && f.sharp == 1 && un != 0) || (f.conversion == 'p'))
	{	
		if (f.conversion == 'x' || (f.conversion == 'p'))
			ft_putstr("0x");
		if (f.conversion == 'X')
			ft_putstr("0X");
	}
	if (f.presicion > (int)ft_strlen(pr))
		length += presicions(f.presicion - ft_strlen(pr));
	if ((f.presicion == 0 || f.presicion == -2) && (un == 0))
		length--;
	else
		ft_putstr(pr);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}
