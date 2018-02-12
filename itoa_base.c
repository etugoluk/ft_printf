
#include "ft_printf.h"

int pow_function(int n, int pow)
{
	int result;
	int i;

	result = 1;
	i = 0;
	if (pow < 0)
		return (0);
	while (i++ < pow)
	{
		result *= n;
	}
	return (result);
}

char mod(int n, int k)
{
	char c;

	if (n >= 0 && n <= 9)
		c = n + 48;
	else if (k == 0)
		c = n - 10 + 97;
	else if (k == 1)
		c = n - 10 + 65;
	else
		c = '\0';
	return (c); 
}

char *itoa_base(int n, int base, int k)
{
	int i;
	char *number;

	i = 1;
	while (pow_function(base, i) <= n)
		i++;
	number = (char *)malloc(sizeof(char) * (i + 1));
	number[i] = '\0';
	i--;
	while (i >= 0)
	{
		number[i] = mod(n % base, k);
		n = n / base;
		i--;
	}
	return (number);
}

// int main()
// {
// 	printf("%s\n", itoa_base(125, 8, 1));
// 	printf("%s\n", itoa_base(125, 16, 1));
// 	printf("%s\n", itoa_base(256, 8, 1));
// 	printf("%s\n", itoa_base(256, 16, 1));
// 	return (0);
// }