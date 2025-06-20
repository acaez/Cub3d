/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:49:47 by acaes             #+#    #+#             */
/*   Updated: 2025/06/20 08:49:47 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ptf.h"

int	ft_print_nbr(int n)
{
	int	i;

	if (n == -2147483648)
		return (ft_print_str("-2147483648"));
	i = 0;
	if (n < 0)
	{
		if (ft_secure_char('-') < 0)
			return (-1);
		n = -n;
		i++;
	}
	if (n >= 10)
	{
		i += ft_print_nbr(n / 10);
		if (i < 0)
			return (-1);
	}
	if (ft_secure_char("0123456789"[n % 10]) < 0)
		return (-1);
	i++;
	return (i);
}
