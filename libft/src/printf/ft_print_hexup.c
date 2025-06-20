/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:49:43 by acaes             #+#    #+#             */
/*   Updated: 2025/06/20 08:49:43 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
