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

static int	is_valid_spec_x_width(t_arg **ainfo, t_data **aout)
{
	int	tmp;

	tmp = 0;
	if ((*ainfo)->width == (*aout)->width && (*ainfo)->precis > (*aout)->len)
	{
		tmp = (*ainfo)->width - (*ainfo)->precis - 2;
		if (tmp > 0)
			return (0);
	}
	return (1);
}

static void	handle_right_hlpr0(t_arg **ainfo, t_data **aout, int *ai)
{
	int	j;

	j = 0;
	if ((is_plus_flag(ainfo) && is_valid_width(ainfo, aout)) ||
		is_space_flag(ainfo))
		j = 1;
	else if (is_hash_flag(ainfo) && ft_strcmp((*aout)->s_arg, "0") != 0 &&
		((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
		j = 2;
	else if (((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i') &&
			*(*aout)->s_arg == '-')
		j = 1;
	ft_memset(((*aout)->presult), ' ', *ai - j);
	(*aout)->presult += (*ai - j);
	if (j == 2)
		*ai = (*ainfo)->precis - (*aout)->len;
	else
		*ai = (*ainfo)->precis - (*aout)->len + j;
}

static void	handle_right_hlpr1(t_arg **ainfo, t_data **aout, int *ai)
{
	if ((*ainfo)->precis == 0 && ft_strcmp((*aout)->s_arg, "0") == 0 &&
		(!is_hash_flag(ainfo) || (is_hash_flag(ainfo) &&
		((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))))
		*ai = (*aout)->width;
	else
		*ai = (*aout)->width - (*aout)->len;
}

static void	is_neg(t_arg **ainfo, t_data **aout, char c, int *aj)
{
	if (*(*aout)->s_arg == '-' && c == '0' &&
		((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
		*aj = 1;
}

void		handle_right_just(t_arg **ainfo, t_data **aout, char c)
{
	int	i;
	int	j;

	j = 0;
	if ((*ainfo)->spec == 'p' || ((is_hash_flag(ainfo) &&
		((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
		&& is_valid_spec_x_width(ainfo, aout))))
		i = (*aout)->width - (*aout)->len - 2;
	else if ((*ainfo)->precis != -1 && (*ainfo)->width != -1 &&
			(*ainfo)->width > (*ainfo)->precis)
	{
		i = (*aout)->width - (*ainfo)->precis;
		if ((*ainfo)->precis > (*aout)->len)
			handle_right_hlpr0(ainfo, aout, &i);
		else if ((*ainfo)->precis < (*aout)->len && is_dioux(ainfo))
			handle_right_hlpr1(ainfo, aout, &i);
		else if ((*aout)->len > (*ainfo)->precis && (*ainfo)->spec != 's')
			i = (*aout)->width - (*aout)->len;
	}
	else
		i = (*aout)->width - (*aout)->len;
	handle_right_pad(ainfo, aout, c, &i);
	is_neg(ainfo, aout, c, &j);
	ft_memcpy(((*aout)->presult) + i, (*aout)->s_arg + j,
				(*aout)->width - ((*aout)->presult - (*aout)->result) - i);
}
