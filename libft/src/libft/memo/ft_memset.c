/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:24:10 by acaes             #+#    #+#             */
/*   Updated: 2025/04/10 22:24:10 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*string;

	string = (unsigned char *)str;
	while (n > 0)
	{
		*(string++) = (unsigned char)c;
		n--;
	}
	return (str);
}
