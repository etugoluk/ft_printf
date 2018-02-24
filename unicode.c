
#include "ft_printf.h"

int bits(wchar_t chr)
{
	//if (chr < (1 << 7))
	if (chr <= 0x7F)
		return (1);
	//else if (chr < (1 << 11))
	else if (chr <= 0x7FF)
		return (2);
	//else if (chr < (1 << 16))
	else if (chr <= 0xFFFF)
		return (3);
	else if (chr <= 0x10FFFF)
	//else if (chr < (1 << 21))
		return (4);
	return (0);
}

void to_unicode(wchar_t chr)
{
	if (chr <= 0x7F)
		ft_putchar(chr);
	else if (chr <= 0x7FF)
	{
		ft_putchar((chr >> 6) + 0xC0);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0xFFFF)
	{
		ft_putchar((chr >> 12) + 0xE0);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0x10FFFF)
	{
		ft_putchar((chr >> 18) + 0xF0);
		ft_putchar(((chr >> 12) & 0x3F) + 0x80);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
}
