/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:47:10 by acaes             #+#    #+#             */
/*   Updated: 2025/06/20 08:47:10 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
