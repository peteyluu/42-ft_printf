/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:49:13 by pluu              #+#    #+#             */
/*   Updated: 2017/01/09 16:59:40 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char *pd;

	pd = dst;
	while (*src)
		*pd++ = *src++;
	*pd = '\0';
	return (dst);
}