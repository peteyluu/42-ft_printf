/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:56:38 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:56:39 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static char	get_pad_ch(t_arg **ainfo, t_data **aout)
{
	if (((is_zero_flag(ainfo) && !is_left_just(ainfo) &&
		(((*ainfo)->precis == -1 && (*ainfo)->width > (*aout)->len) ||
		((*ainfo)->precis == 0 && (*ainfo)->spec != 'd' &&
		(*ainfo)->spec != 'i'))) || ((*ainfo)->spec != 's' &&
		(*ainfo)->precis > (*aout)->len) || ((*ainfo)->spec != 's' &&
		((*ainfo)->precis >= (*aout)->width ||
		(*ainfo)->precis > (*aout)->len)) ||
		((*ainfo)->precis == (*aout)->len &&
		*(*aout)->s_arg == '-')))
		return ('0');
	else if ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O' ||
			(*ainfo)->spec == 'u' || (*ainfo)->spec == 'U' ||
			(*ainfo)->spec == 'x' || (*ainfo)->spec == 'X' ||
			(*ainfo)->spec == 'D')
	{
		if ((*ainfo)->precis >= (*aout)->width
			|| (*ainfo)->precis > (*aout)->len)
			return ('0');
		else if ((*ainfo)->precis == -1 && (*aout)->width > (*aout)->len &&
				is_zero_flag(ainfo) && !is_left_just(ainfo))
			return ('0');
	}
	return (' ');
}

char		find_flag(t_arg **ainfo, t_data **aout)
{
	if (is_plus_flag(ainfo) && *(*aout)->s_arg != '-')
		return ('+');
	else if (is_space_flag(ainfo))
		return (' ');
	else if ((is_hash_flag(ainfo) || (*ainfo)->spec == 'p'))
	{
		if ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'p')
			return ('x');
		else if ((*ainfo)->spec == 'X')
			return ('X');
		return ('0');
	}
	else if (is_zero_flag(ainfo) && (*ainfo)->precis > (*aout)->len)
		return ('0');
	return (0);
}

int			is_width_pad(t_arg **ainfo, int s_len)
{
	if ((((*ainfo)->width > (*ainfo)->precis && (*ainfo)->precis != -1 &&
		(!is_hash_flag(ainfo) || (*ainfo)->spec == 'x' ||
		(*ainfo)->spec == 'X')) || (((*ainfo)->width > s_len) &&
		(*ainfo)->width != -1)) || (*ainfo)->precis > s_len)
		return (1);
	return (0);
}

void		width_padding(t_arg **ainfo, t_data **aout)
{
	char	pad_ch;

	pad_ch = get_pad_ch(ainfo, aout);
	if (is_left_just(ainfo) || ((*ainfo)->spec == 'p' && is_zero_flag(ainfo)))
		handle_left_just(ainfo, aout, pad_ch);
	else
		handle_right_just(ainfo, aout, pad_ch);
}
