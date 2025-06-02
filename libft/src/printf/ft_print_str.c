#include "../../inc/ptf.h"

int	ft_print_str(char *s)
{
	if (!s)
		s = NULL_STR;
	if (write(1, s, ft_strlen(s)) < 0)
		return (-1);
	return (ft_strlen(s));
}
