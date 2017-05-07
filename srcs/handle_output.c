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

static int	pop_ox_prefix(t_arg **ainfo, t_data **aoutput)
{
	int	tmp;

	tmp = 0;
	*(*aoutput)->presult++ = '0';
	tmp = 1;
	if ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
	{
		*(*aoutput)->presult++ = (*ainfo)->spec;
		tmp = 2;
	}
	return (tmp);
}

static void	pop_res_hlpr(t_arg **ainfo, t_data **aoutput)
{
	int	 offset_width;

	offset_width = 0;
	if ((*ainfo)->flags[PLUS_IDX] && *(*aoutput)->s_arg != '-'
		&& ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i' || (*ainfo)->spec == 'D'))
	{
		*(*aoutput)->presult++ = '+';
		offset_width++;
	}
	if ((*ainfo)->flags[SPACE_IDX] && (*ainfo)->spec != 'p' && is_valid_space_flag(ainfo, aoutput))
	{
		*(*aoutput)->presult++ = ' ';
		offset_width++;
	}
	if ((*ainfo)->flags[HASH_IDX] && ft_strcmp((*aoutput)->s_arg, "0") != 0
		&& ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O' || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
		offset_width += pop_ox_prefix(ainfo, aoutput);
	if ((*ainfo)->spec == 'p')
	{
		*(*aoutput)->presult++ = '0';
		*(*aoutput)->presult++ = 'x';
		offset_width += 2;
	}
	ft_memcpy(((*aoutput)->presult), (*aoutput)->s_arg, (*aoutput)->width - offset_width);
}

int	populate_result(t_arg **ainfo, t_data **aoutput)
{
	(*aoutput)->len = ft_strlen((*aoutput)->s_arg);	
	if ((*aoutput)->len == 0 && ((*ainfo)->spec == 'c' || (*ainfo)->spec == 'C'))
		(*aoutput)->len = 1;
	get_min_width(ainfo, aoutput);
	get_precis(ainfo, aoutput);
	update_result(ainfo, aoutput);
	if (is_width_pad(ainfo, (*aoutput)->len))
		width_padding(ainfo, aoutput);
	else
		pop_res_hlpr(ainfo, aoutput);
	return ((*aoutput)->width);
}
