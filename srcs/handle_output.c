/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:56:11 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:56:12 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	pop_ox_prefix(t_arg **ainfo, t_data **aout)
{
	int	tmp;

	tmp = 0;
	*(*aout)->presult++ = '0';
	tmp = 1;
	if ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
	{
		*(*aout)->presult++ = (*ainfo)->spec;
		tmp = 2;
	}
	return (tmp);
}

static void	pop_res_hlpr(t_arg **ainfo, t_data **aout, int offset)
{
	if ((*ainfo)->flags[PLUS_IDX] && *(*aout)->s_arg != '-' &&
		((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i' ||
		(*ainfo)->spec == 'D'))
	{
		*(*aout)->presult++ = '+';
		offset++;
	}
	if ((*ainfo)->flags[SPACE_IDX] && (*ainfo)->spec != 'p' &&
		is_valid_space_flag(ainfo, aout))
	{
		*(*aout)->presult++ = ' ';
		offset++;
	}
	if ((*ainfo)->flags[HASH_IDX] && ft_strcmp((*aout)->s_arg, "0") != 0 &&
		((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O' ||
		(*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
		offset += pop_ox_prefix(ainfo, aout);
	if ((*ainfo)->spec == 'p')
	{
		*(*aout)->presult++ = '0';
		*(*aout)->presult++ = 'x';
		offset += 2;
	}
	ft_memcpy(((*aout)->presult), (*aout)->s_arg, (*aout)->width - offset);
}

int			populate_result(t_arg **ainfo, t_data **aout)
{
	int	offset;

	offset = 0;
	(*aout)->len = ft_strlen((*aout)->s_arg);
	if ((*aout)->len == 0 && ((*ainfo)->spec == 'c' || (*ainfo)->spec == 'C'))
		(*aout)->len = 1;
	get_min_width(ainfo, aout);
	get_precis(ainfo, aout);
	update_result(ainfo, aout);
	if (is_width_pad(ainfo, (*aout)->len))
		width_padding(ainfo, aout);
	else
		pop_res_hlpr(ainfo, aout, offset);
	return ((*aout)->width);
}
