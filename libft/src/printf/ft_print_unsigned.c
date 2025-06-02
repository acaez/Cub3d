#include "../../inc/ptf.h"

int	ft_print_unsigned(unsigned int n)
{
	int	i;

	i = 0;
	if (n > 9)
	{
		i += ft_print_unsigned(n / 10);
		if (i < 0)
			return (-1);
	}
	if (ft_secure_char("0123456789"[n % 10]) < 0)
		return (-1);
	i++;
	return (i);
}