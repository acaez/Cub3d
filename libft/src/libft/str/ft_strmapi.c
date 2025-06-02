/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:30:20 by acaes             #+#    #+#             */
/*   Updated: 2025/04/13 18:30:20 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

char	*ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
	char			*map;
	unsigned int	i;
	size_t			len;

	if (!str || !f)
		return (NULL);
	len = ft_strlen(str);
	map = (char *)malloc(sizeof(char) * (len + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < len)
	{
		map[i] = (*f)(i, str[i]);
		i++;
	}
	map[i] = '\0';
	return (map);
}
