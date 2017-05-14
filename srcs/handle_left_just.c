/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_left_just.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:56:49 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:56:51 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	handle_left_prefix(t_arg **ainfo, t_data **aout)
{
	(*aout)->flag = find_flag(ainfo, aout);
	if ((*aout)->flag)
	{
		if ((*aout)->flag == 'x' || (*aout)->flag == 'X')
		{
			*(*aout)->presult++ = '0';
			*(*aout)->presult++ = (*aout)->flag;
			return (2);
		}
		else if (!is_hash_flag(ainfo) || (is_hash_flag(ainfo)
				&& (*ainfo)->precis <= 1))
		{
			*(*aout)->presult++ = (*aout)->flag;
			return (1);
		}
	}
	return (0);
}

static int	handle_left_precis(t_arg **ainfo, t_data **aout, char c)
{
	int	precis;

	precis = 0;
	if ((*ainfo)->precis > (*aout)->len && ((*ainfo)->spec == 'd' ||
		(*ainfo)->spec == 'i' || (*ainfo)->spec == 'o' ||
		(*ainfo)->spec == 'O' || (*ainfo)->spec == 'u' ||
		(*ainfo)->spec == 'U' || (*ainfo)->spec == 'x' ||
		(*ainfo)->spec == 'X' || (*ainfo)->spec == 'D'))
	{
		precis = (*ainfo)->precis - (*aout)->len;
		ft_memset((*aout)->presult, c, precis);
		(*aout)->presult += precis;
	}
	return (precis);
}

void		handle_left_just(t_arg **ainfo, t_data **aout, char c)
{
	int	i;
	int	j;
	int	k;

	if ((*ainfo)->precis != -1 && (*ainfo)->precis != 0 &&
		(*ainfo)->precis < (*aout)->len && ((*ainfo)->spec == 's' ||
		(*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
		i = (*ainfo)->precis;
	else if ((*ainfo)->precis == 0 && (*ainfo)->precis < (*aout)->len &&
			ft_strcmp((*aout)->s_arg, "0") == 0 &&
			(((!is_hash_flag(ainfo) && ((*ainfo)->spec == 'o' ||
			(*ainfo)->spec == 'u' || (*ainfo)->spec == 'U')))
			|| (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
		i = 0;
	else
		i = (*aout)->len;
	j = handle_left_prefix(ainfo, aout);
	k = handle_left_precis(ainfo, aout, c);
	ft_memcpy((*aout)->presult, (*aout)->s_arg, i);
	if (k)
		ft_memset((*aout)->presult + i, ' ', (*aout)->width - i - j - k);
	else
		ft_memset(((*aout)->presult) + i, c, (*aout)->width - i - j);
}
