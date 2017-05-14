/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uintmax_to_a_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:55:49 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:55:50 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	uintmax_numlen(uintmax_t n, int b)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= b;
	}
	return (len);
}

char		*uintmax_to_a_base(uintmax_t value, int base, char spec)
{
	int		len;
	char	*s;
	char	*ps;
	char	*b;

	b = (spec == 'X' ? "0123456789ABCDEF" : "0123456789abcdef");
	if (value == 0)
	{
		if (!(s = ft_strnew(1)))
			return (NULL);
		*s = '0';
		return (s);
	}
	len = uintmax_numlen(value, base);
	if (!(s = ft_strnew(len)))
		return (NULL);
	ps = s;
	while (value)
	{
		*ps++ = b[(value % base)];
		value /= base;
	}
	return (ft_strrev(s));
}
