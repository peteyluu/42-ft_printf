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

static int	incr_width_hlpr(t_arg **ainfo, t_data **aoutput)
{
	int	tmp;

	tmp = 0;
	if ((*aoutput)->width == 1 || ((*ainfo)->precis > (*aoutput)->len && (*ainfo)->precis >= (*aoutput)->width)
		|| ((*aoutput)->len >= (*ainfo)->width && (*aoutput)->len >= (*ainfo)->precis))
		return (2);
	else if ((*aoutput)->width == 2)
		return (1);
	else if ((*ainfo)->width > (*aoutput)->len && (*aoutput)->len > (*ainfo)->precis)
		tmp = (*aoutput)->width - (*aoutput)->len;
	else if ((*aoutput)->width > (*ainfo)->precis && (*ainfo)->precis > (*aoutput)->len)
		tmp = (*aoutput)->width - (*ainfo)->precis;
	return (tmp <= 1 ? tmp : 0);
}

static int	increment_width(t_arg **ainfo, t_data **aoutput)
{
	int	cnt;

	cnt = 0;
	if (is_plus_flag(ainfo) && !is_valid_width(ainfo, aoutput) && *(*aoutput)->s_arg != '-' && (*ainfo)->spec != 'p'
		&& ((*aoutput)->len >= (*aoutput)->width || (*ainfo)->precis > (*aoutput)->len))
		cnt++;
	if (is_space_flag(ainfo) && is_valid_space_flag(ainfo, aoutput)
		&& ((*aoutput)->width <= (*ainfo)->precis || (*aoutput)->width <= (*aoutput)->len))
		cnt++;
	if (is_hash_flag(ainfo) && ft_strcmp((*aoutput)->s_arg, "0") != 0)
	{
		if ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
			cnt += incr_width_hlpr(ainfo, aoutput);
		else if ((*aoutput)->len >= (*aoutput)->width && ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O'))
			cnt++;
	}
	if ((*ainfo)->precis > (*aoutput)->len && (*ainfo)->precis >= (*aoutput)->width && *(*aoutput)->s_arg == '-'
		&& ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
		cnt++;
	if ((*ainfo)->spec == 'p')
		cnt += incr_width_hlpr(ainfo, aoutput);
	return (cnt);
}

void	update_result(t_arg **ainfo, t_data **aoutput)
{
	(*aoutput)->result = ft_strnew((*aoutput)->width += increment_width(ainfo, aoutput));
	(*aoutput)->presult = (*aoutput)->result;
}
