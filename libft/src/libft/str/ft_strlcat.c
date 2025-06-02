/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:30:11 by acaes             #+#    #+#             */
/*   Updated: 2025/04/13 18:30:11 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	lsrc;
	size_t	ldst;

	lsrc = ft_strlen(src);
	ldst = ft_strlen(dst);
	if (ldst >= n)
		return (n + lsrc);
	else if (lsrc < (n - ldst))
		ft_memcpy(dst + ldst, src, lsrc + 1);
	else
	{
		ft_memcpy(dst + ldst, src, n - ldst - 1);
		dst[n - 1] = '\0';
	}
	return (ldst + lsrc);
}
