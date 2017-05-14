/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:56:19 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:56:20 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static void	get_s_precis(t_arg **ainfo, t_data **aout)
{
	if ((*ainfo)->width > (*ainfo)->precis)
		(*aout)->width = (*ainfo)->width;
	else if ((*ainfo)->precis >= (*ainfo)->width
			&& (*ainfo)->precis <= (*aout)->len)
		(*aout)->width = (*ainfo)->precis;
	else if ((*ainfo)->precis > (*aout)->width && (*aout)->width < (*aout)->len)
		(*aout)->width = (*aout)->len;
}

static void	get_di_precis(t_arg **ainfo, t_data **aout)
{
	if ((*ainfo)->precis == 0 && ft_strcmp((*aout)->s_arg, "0") == 0)
	{
		if ((*ainfo)->width == -1)
			(*aout)->width = 0;
	}
	else if ((*ainfo)->precis > (*aout)->width)
		(*aout)->width = (*ainfo)->precis;
}

static void	get_ouxdp_precis(t_arg **ainfo, t_data **aout)
{
	if ((*ainfo)->precis == 0 && ft_strcmp((*aout)->s_arg, "0") == 0
		&& (*ainfo)->width <= 0)
	{
		if (!is_hash_flag(ainfo) || (*ainfo)->spec == 'x'
			|| (*ainfo)->spec == 'X' || (*ainfo)->spec == 'p')
			(*aout)->width = 0;
	}
	else if ((*ainfo)->precis > (*aout)->width)
		(*aout)->width = (*ainfo)->precis;
}

void		get_precis(t_arg **ainfo, t_data **aout)
{
	if ((*ainfo)->precis != -1)
	{
		if ((*ainfo)->spec == 's')
			get_s_precis(ainfo, aout);
		else if (((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
			get_di_precis(ainfo, aout);
		else if ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O'
				|| (*ainfo)->spec == 'u' || (*ainfo)->spec == 'U'
				|| (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'
				|| (*ainfo)->spec == 'D' || (*ainfo)->spec == 'p')
			get_ouxdp_precis(ainfo, aout);
	}
}

void		get_min_width(t_arg **ainfo, t_data **aout)
{
	if ((*ainfo)->width != -1)
	{
		if ((*ainfo)->width < (*aout)->len &&
			((*ainfo)->precis != 0 || (*ainfo)->precis == 0))
			(*aout)->width = (*aout)->len;
		else
			(*aout)->width = (*ainfo)->width;
	}
	else
		(*aout)->width = (*aout)->len;
}
