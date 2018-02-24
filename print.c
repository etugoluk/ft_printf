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

	pr = va_arg(*l, char *);
	if (f.presicion < (int)ft_strlen1(pr) && f.presicion >= 0)
		length = f.presicion;
	else if (f.presicion == -2)
		length = f.min_width;
	else
		length = ft_strlen1(pr);
	//printf("min %d\n", length);
	if (f.minus == 0)
	{
		length += right_padding(f.min_width - length, f);
	}
	if (f.presicion != -1 && f.presicion != -2)
		ft_putstrn(pr, f.presicion);
	else if (f.presicion == -2)
	{
		// if (f.min_width >= (int)ft_strlen1(pr))
		// 	right_padding(ft_strlen1(pr), f);
		// else
		//length = length - ft_strlen1(pr) + f.min_width;
		//length = f.min_width;
		right_padding(f.min_width, f);
	}
	else
		ft_putstr(pr);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

int print_S(va_list *l, t_printf f)
{
	wchar_t *ws;
	int length;
	int i;
	int k;

	i = 0;
	k = 0;
	length = 0;
	if (!(ws = va_arg(*l, wchar_t*)))
	{
		ft_putstr("(null)");
		return (6);
	}
	while (ws[i] != '\0')
	{
		length += bits(ws[i]);
		i++;
	}
	i = 0;
	if (f.presicion < length && f.presicion >= 0)
	{
		k += bits(ws[i]);
		while (ws[i] != '\0' && k <= f.presicion)
		{
			k += bits(ws[i + 1]);
			i++;
		}
		k -= bits(ws[i]);
		if (f.presicion > k)
			length = k;
		else
			length = f.presicion;
	}
	if (f.minus == 0)
		length += right_padding(f.min_width - length, f);
	i = 0;
	k = 0;
	if (f.presicion >= 0)
	{
		k += bits(ws[i]);
		while (ws[i] != '\0' && k <= f.presicion)
		{
			to_unicode(ws[i]);
			k += bits(ws[i + 1]);
			i++;
		}
	}
	else if (f.presicion != -2)
		while (ws[i] != '\0')
		{
			to_unicode(ws[i]);
			i++;
		}
	else if (f.presicion == -2)
	{
		// while (ws[i] != '\0')
		// {
		// 	//to_unicode(ws[i]);
		// 	k = bits(ws[i]);
			right_padding(f.min_width,f);
			length = f.min_width;
		// 	i++;
		// }
	}
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

int print_c(va_list *l, t_printf f)
{
	int length;
	char ch;

	length = 0;
	if (f.minus == 0)
		length += right_padding(f.min_width - 1, f);
	ch = (unsigned char)va_arg(*l, int);
	ft_putchar(ch);
	length++;
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	return (length);
}

int print_C(va_list *l, t_printf f)
{
	int length;
	wchar_t wc;

	wc = (wchar_t)va_arg(*l, wint_t);
	length = bits(wc);
	if (f.minus == 0)
		length += right_padding(f.min_width - length, f);
	to_unicode(wc);
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
		if (f.min_width > 0)
			ft_putchar(' ');
		else
			length--;
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
	if (f.sharp == 1 && un != 0 && f.presicion < 0)
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
	if ((f.presicion == 0 || f.presicion == -2) && (un == 0) && (f.sharp == 0))
	{
		if (f.min_width > 0)
			ft_putchar(' ');
		else
			length--;
	}
	else
		ft_putstr(pr);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	free(pr);
	pr = NULL;
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
	{
		if (f.min_width > 0)
			ft_putchar(' ');
		else
			length--;
	}
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
	free(pr);
	pr = NULL;
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
	if ((f.zero == 1 && f.sharp == 1 && un != 0) || (f.conversion == 'p' && f.zero == 1))
	{	
		if (f.conversion == 'x' || (f.conversion == 'p'))
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
	if ((f.zero == 0 && f.sharp == 1 && un != 0) || (f.conversion == 'p' && f.zero == 0))
	{	
		if (f.conversion == 'x' || (f.conversion == 'p'))
			ft_putstr("0x");
		if (f.conversion == 'X')
			ft_putstr("0X");
	}
	if (f.presicion > (int)ft_strlen(pr))
		length += presicions(f.presicion - ft_strlen(pr));
	if ((f.presicion == 0 || f.presicion == -2) && (un == 0))
	{
		if (f.min_width > 0)
			ft_putchar(' ');
		else
			length--;
	}
	else
		ft_putstr(pr);
	if (f.minus == 1)
		length += right_padding(f.min_width - length, f);
	free(pr);
	pr = NULL;
	return (length);
}
