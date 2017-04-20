/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:09:08 by pluu              #+#    #+#             */
/*   Updated: 2017/01/10 17:24:16 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char *ps;

	ps = s;
	while (*ps)
	{
		if (*ps == c)
			return ((char*)ps);
		ps++;
	}
	return ((*ps == c) ? (char*)ps : 0);
}