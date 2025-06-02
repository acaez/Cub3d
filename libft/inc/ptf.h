#ifndef PTF_H
# define PTF_H

# include "libft.h"
# include <stdarg.h>

# ifndef __linux__
#  define NULL_STR "(null)"
#  define NULL_PTR "(nil)"
# else
#  define NULL_STR "(null)"
#  define NULL_PTR "0x0"
# endif

int	ft_print_hexlow(unsigned long n);
int	ft_print_hexup(unsigned long n);
int	ft_print_nbr(int n);
int	ft_print_ptr(void *ptr);
int	ft_print_str(char *s);
int	ft_print_unsigned(unsigned int n);
int	ft_printf(const char *format, ...);
int	ft_secure_char(char c);

#endif
