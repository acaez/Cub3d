#include "../../inc/ptf.h"

int	ft_secure_char(char c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (1);
}
