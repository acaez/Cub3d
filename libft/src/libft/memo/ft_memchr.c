/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:27:12 by acaes             #+#    #+#             */
/*   Updated: 2025/04/13 18:27:12 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*pstr;
	size_t			i;

	pstr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (pstr[i] == (unsigned char)c)
			return ((void *)&pstr[i]);
		i++;
	}
	return (NULL);
}
