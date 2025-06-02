/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:27:02 by acaes             #+#    #+#             */
/*   Updated: 2025/04/13 18:27:02 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdst;

	psrc = (unsigned char *)src;
	pdst = (unsigned char *)dst;
	if (n == 0 || dst == src)
		return (dst);
	if (pdst > psrc)
	{
		while (n > 0)
		{
			n--;
			pdst[n] = psrc[n];
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
