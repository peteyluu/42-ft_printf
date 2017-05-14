/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:56:29 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:56:31 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	incr_width_hlpr(t_arg **ainfo, t_data **aout)
{
	int	tmp;

	tmp = 0;
	if ((*aout)->width == 1 || ((*ainfo)->precis > (*aout)->len &&
		(*ainfo)->precis >= (*aout)->width) ||
		((*aout)->len >= (*ainfo)->width &&
		(*aout)->len >= (*ainfo)->precis))
		return (2);
	else if ((*aout)->width == 2)
		return (1);
	else if ((*ainfo)->width > (*aout)->len && (*aout)->len > (*ainfo)->precis)
		tmp = (*aout)->width - (*aout)->len;
	else if ((*aout)->width > (*ainfo)->precis &&
			(*ainfo)->precis > (*aout)->len)
		tmp = (*aout)->width - (*ainfo)->precis;
	return (tmp <= 1 ? tmp : 0);
}

static int	increment_width(t_arg **ainfo, t_data **aout)
{
	int	cnt;

	cnt = 0;
	if (is_plus_flag(ainfo) && !is_valid_width(ainfo, aout) &&
		*(*aout)->s_arg != '-' && (*ainfo)->spec != 'p' &&
		((*aout)->len >= (*aout)->width || (*ainfo)->precis > (*aout)->len))
		cnt++;
	if (is_space_flag(ainfo) && is_valid_space_flag(ainfo, aout) &&
		((*aout)->width <= (*ainfo)->precis || (*aout)->width <= (*aout)->len))
		cnt++;
	if (is_hash_flag(ainfo) && ft_strcmp((*aout)->s_arg, "0") != 0)
	{
		if ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
			cnt += incr_width_hlpr(ainfo, aout);
		else if ((*aout)->len >= (*aout)->width &&
				((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O'))
			cnt++;
	}
	if ((*ainfo)->precis > (*aout)->len && (*ainfo)->precis >= (*aout)->width &&
		*(*aout)->s_arg == '-' &&
		((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
		cnt++;
	if ((*ainfo)->spec == 'p')
		cnt += incr_width_hlpr(ainfo, aout);
	return (cnt);
}

void		update_result(t_arg **ainfo, t_data **aout)
{
	(*aout)->result = ft_strnew((*aout)->width += increment_width(ainfo, aout));
	(*aout)->presult = (*aout)->result;
}
