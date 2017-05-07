/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_right_just.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:56:58 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:56:59 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	is_valid_spec_x_width(t_arg **ainfo, t_data **aoutput)
{
	int	tmp;

	tmp = 0;
	if ((*ainfo)->width == (*aoutput)->width && (*ainfo)->precis > (*aoutput)->len)
	{
		tmp = (*ainfo)->width - (*ainfo)->precis - 2;
		if (tmp > 0)
			return (0);
	}
	return (1);
}

static void	handle_right_hlpr0(t_arg **ainfo, t_data **aoutput, int *ai)
{
	int	j;

	j = 0;
	if ((is_plus_flag(ainfo) && is_valid_width(ainfo, aoutput)) || is_space_flag(ainfo))
		j = 1;
	else if (is_hash_flag(ainfo) && ft_strcmp((*aoutput)->s_arg, "0") != 0 &&
		((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
		j = 2;
	else if (((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i') && *(*aoutput)->s_arg == '-')
		j = 1;
	ft_memset(((*aoutput)->presult), ' ', *ai - j);
	(*aoutput)->presult += (*ai - j);
	if (j == 2)
		*ai = (*ainfo)->precis - (*aoutput)->len;
	else
		*ai = (*ainfo)->precis - (*aoutput)->len + j;
}

static void	handle_right_hlpr1(t_arg **ainfo, t_data **aoutput, int *ai)
{
	if ((*ainfo)->precis == 0 && ft_strcmp((*aoutput)->s_arg, "0") == 0 &&
		(!is_hash_flag(ainfo) || (is_hash_flag(ainfo) && ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))))
		*ai = (*aoutput)->width;
	else
		*ai = (*aoutput)->width - (*aoutput)->len;
}

void	handle_right_just(t_arg **ainfo, t_data **aoutput, char c)
{
	int	i;
	int	j;

	j = 0;
	if ((*ainfo)->spec == 'p' || ((is_hash_flag(ainfo) && ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
		&& is_valid_spec_x_width(ainfo, aoutput))))
		i = (*aoutput)->width - (*aoutput)->len - 2;
	else if ((*ainfo)->precis != -1 && (*ainfo)->width != -1 && (*ainfo)->width > (*ainfo)->precis)
	{
		i = (*aoutput)->width - (*ainfo)->precis;
		if ((*ainfo)->precis > (*aoutput)->len)
			handle_right_hlpr0(ainfo, aoutput, &i);
		else if ((*ainfo)->precis < (*aoutput)->len && ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'
			|| (*ainfo)->spec == 'o' || (*ainfo)->spec == 'O' || (*ainfo)->spec == 'u'
			|| (*ainfo)->spec == 'U' || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
			handle_right_hlpr1(ainfo, aoutput, &i);
		else if ((*aoutput)->len > (*ainfo)->precis && (*ainfo)->spec != 's')
			i = (*aoutput)->width - (*aoutput)->len;
	}
	else
		i = (*aoutput)->width - (*aoutput)->len;
	handle_right_pads(ainfo, aoutput, c, &i);
	if (*(*aoutput)->s_arg == '-' && c == '0' && ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
		j = 1;
	ft_memcpy(((*aoutput)->presult) + i, (*aoutput)->s_arg + j, (*aoutput)->width - ((*aoutput)->presult - (*aoutput)->result) - i);
}
