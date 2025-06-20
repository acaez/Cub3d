/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:49:50 by acaes             #+#    #+#             */
/*   Updated: 2025/06/20 08:49:50 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
