#include "../../inc/ptf.h"

int	ft_print_hexup(unsigned long n)
{
	int	i;

	if (n == 0)
		return (ft_secure_char('0'));
	i = 0;
	if (n >= 16)
	{
		i += ft_print_hexup(n / 16);
		if (i < 0)
			return (-1);
	}
	if (ft_secure_char("0123456789ABCDEF"[n % 16]) < 0)
		return (-1);
	i++;
	return (i);
}
