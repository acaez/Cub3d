/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:42:05 by acaes             #+#    #+#             */
/*   Updated: 2025/04/10 16:42:05 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
