/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:02:28 by pluu              #+#    #+#             */
/*   Updated: 2017/01/19 15:17:00 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*s1;
	const char	*s2;

	s1 = dst;
	s2 = src;
	while (n--)
		*s1++ = *s2++;
	return (dst);
}