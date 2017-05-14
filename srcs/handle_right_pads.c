/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_right_pads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:57:04 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:57:05 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static void	handle_right_pads0(t_data **aout, char c, int *ai)
{
	(*ai)--;
	if (c == ' ')
	{
		ft_memset((*aout)->presult, c, *ai);
		*((*aout)->presult++ + *ai) = (*aout)->flag;
	}
	else
	{
		*(*aout)->presult++ = (*aout)->flag;
		ft_memset((*aout)->presult, c, *ai);
	}
}

static void	handle_right_pads1(t_data **aout, char c, int *ai)
{
	if (*ai)
	{
		if (c == ' ')
		{
			ft_memset((*aout)->presult, c, *ai);
			*((*aout)->presult + *ai) = '0';
			*((*aout)->presult + *ai + 1) = (*aout)->flag;
		}
		else
		{
			*((*aout)->presult) = '0';
			*((*aout)->presult + 1) = (*aout)->flag;
			ft_memset((*aout)->presult + 2, c, *ai);
		}
	}
	else
	{
		*((*aout)->presult) = '0';
		*((*aout)->presult + 1) = (*aout)->flag;
	}
	(*ai) += 2;
}

void		handle_right_pad(t_arg **ainfo, t_data **aout, char c, int *ai)
{
	(*aout)->flag = find_flag(ainfo, aout);
	if ((*aout)->flag)
	{
		if (*ai > 1 && (*aout)->flag != 'x' && (*aout)->flag != 'X')
			handle_right_pads0(aout, c, ai);
		else if ((*aout)->flag == 'x' || (*aout)->flag == 'X')
			handle_right_pads1(aout, c, ai);
		else
			*(*aout)->presult = (*aout)->flag;
	}
	else
	{
		if (*(*aout)->s_arg == '-' && c == '0' &&
			((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
			*(*aout)->presult++ = '-';
		ft_memset((*aout)->presult, c, *ai);
	}
}
