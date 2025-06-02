#include "../../inc/ptf.h"

static int	ft_flag(const char *format, va_list *args)
{
	if (*format == 'c')
		return (ft_secure_char(va_arg(*args, int)));
	else if (*format == 's')
		return (ft_print_str(va_arg(*args, char *)));
	else if (*format == 'p')
		return (ft_print_ptr(va_arg(*args, void *)));
	else if (*format == 'd')
		return (ft_print_nbr(va_arg(*args, int)));
	else if (*format == 'u')
		return (ft_print_unsigned(va_arg(*args, unsigned int)));
	else if (*format == 'x')
		return (ft_print_hexlow(va_arg(*args, unsigned int)));
	else if (*format == 'X')
		return (ft_print_hexup(va_arg(*args, unsigned int)));
	else if (*format == '%')
		return (ft_secure_char('%'));
	else
		return (ft_secure_char(*format));
}

static int	ft_format(const char *format, va_list *args)
{
	int	i;
	int	len;

	len = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			i = ft_flag(format, args);
			if (i == -1)
				return (-1);
			len += i;
		}
		else
		{
			i = ft_secure_char(*format);
			if (i == -1)
				return (-1);
			len += i;
		}
		format++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (0);
	len = 0;
	va_start(args, format);
	len = ft_format(format, &args);
	va_end(args);
	return (len);
}
