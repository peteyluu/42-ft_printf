/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:55:40 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:55:41 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static char	*handle_wch(wchar_t wc)
{
	int	num_bytes;
	char	*s;
	char	*ps;

	num_bytes = get_byte_cnt(wc);
	s = ft_strnew(num_bytes);
	ps = s;
	unicode_to_utf8(wc, &s);
	return (ps);
}

int		get_byte_cnt(wchar_t wc)
{
	if (wc < 128)
		return (1);
	else if (wc < 2048)
		return (2);
	else if (wc < 65536)
		return (3);
	else
		return (4);
}

void		handle_bc_arg(t_data **aoutput, t_misc **amisc)
{
	(*aoutput)->s_arg = handle_wch(va_arg((*amisc)->ap, wchar_t));
	(*aoutput)->free_arg = 1;
}
