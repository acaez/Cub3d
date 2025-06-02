#include "../../inc/ptf.h"

int	ft_print_ptr(void *ptr)
{
	int	i;

	if (!ptr)
		return (ft_print_str(NULL_PTR));
	i = 0;
	i += ft_print_str("0x");
	if (i < 0)
		return (-1);
	return (i + ft_print_hexlow((unsigned long)ptr));
}
