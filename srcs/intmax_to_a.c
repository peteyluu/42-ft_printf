/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intmax_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:55:57 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:55:58 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	intmax_numlen(intmax_t n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*intmax_handle_zero(void)
{
	char	*s;

	if (!(s = ft_strnew(2)))
		return (NULL);
	*s = '0';
	return (s);
}

char		*intmax_to_a(intmax_t value)
{
	int		isneg;
	int		len;
	char	*s;
	char	*ps;

	isneg = 0;
	if (value == 0)
		return (intmax_handle_zero());
	else if (value < 0)
		isneg = 1;
	len = intmax_numlen(value);
	if (!(s = ft_strnew(len + isneg)))
		return (NULL);
	ps = s;
	if (isneg)
		*ps++ = '-';
	while (value)
	{
		if (isneg)
			*ps++ = ((value % 10) * -1) + 48;
		else
			*ps++ = (value % 10) + 48;
		value /= 10;
	}
	return (ft_strrev(s));
}
