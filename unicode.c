
#include "ft_printf.h"

int bits(int n)
{
	if (n <= 7)
		return (1);
	else if (n <= 11)
		return (2);
	else if (n <= 16)
		return (3);
	else
		return (4);
}

int to_char(char *s)
{
	int i;
	int k;
	int result;

	i = 7;
	result = 0;
	k = 0;
	while (i >= 0)
	{
		if (s[k] == '1')
			result = result + pow_function(2, i);
		k++;
		i--;
	}
	return (result);
}

void to_unicode(char *s)
{
	int n;
	char *str;
	char *tmp;
	int dop;
	int k;

	//printf("%s\n", s);
	n = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * bits(n));
	tmp = (char *)malloc(sizeof(char) * 8);
	k = bits(n);
	//printf("%d\n", k);
	dop = 7;
	if (k == 4)
	{
		tmp[0] = '1';
		tmp[1] = '0';
		while (dop != 1)
		{
			tmp[dop--] = s[--n];
		}
		str[3] = (char)to_char(tmp);
		dop = 7;
		while (dop != 1)
		{
			tmp[dop--] = s[--n];
		}
		str[2] = (char)to_char(tmp);
		dop = 7;
		while (dop != 1)
		{
			tmp[dop--] = s[--n];
		}
		str[1] = (char)to_char(tmp);
		dop = 7;
		tmp[0] = '1';
		tmp[1] = '1';
		tmp[2] = '1';
		tmp[3] = '1';
		tmp[4] = '0';
		while (dop != 4)
		{
			if (n > 0)
				tmp[dop--] = s[--n];
			else
				tmp[dop--] = '0';
		}
		str[0] = (char)to_char(tmp);
	}
	else if (k == 3)
	{
		//printf("%s\n", "here3");
		tmp[0] = '1';
		tmp[1] = '0';
		while (dop != 1)
		{
			tmp[dop--] = s[--n];
		}
		str[2] = (char)to_char(tmp);
		//printf("%c\n", str[2]);
		dop = 7;
		while (dop != 1)
		{
			tmp[dop--] = s[--n];
		}
		str[1] = (char)to_char(tmp);
		//printf("%c\n", str[1]);
		dop = 7;
		tmp[0] = '1';
		tmp[1] = '1';
		tmp[2] = '1';
		tmp[3] = '0';
		while (dop != 3)
		{
			if (n > 0)
				tmp[dop--] = s[--n];
			else
				tmp[dop--] = '0';
		}
		str[0] = (char)to_char(tmp);
		//printf("%c\n", str[0]);
	}
	else if (k == 2)
	{
		//printf("%s\n", "here2");
		tmp[0] = '1';
		tmp[1] = '0';
		while (dop != 1)
		{
			tmp[dop--] = s[--n];
		}
		//printf("%s\n", tmp);
		str[1] = (char)to_char(tmp);
		dop = 7;
		tmp[0] = '1';
		tmp[1] = '1';
		tmp[2] = '0';
		while (dop != 2)
		{
			if (n > 0)
			{
				tmp[dop--] = s[--n];
			}
			else
				tmp[dop--] = '0';
		}
		//printf("%s\n", tmp);
		str[0] = (char)to_char(tmp);
	}
	else if (k == 1)
	{
		tmp[0] = '0';
		while (dop != 0)
		{
			if (n > 0)
				tmp[dop--] = s[--n];
			else
				tmp[dop--] = '0';
		}
		str[0] = (char)to_char(tmp);
	}
	ft_putstr(str);
}
