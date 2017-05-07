/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width_precis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:54:18 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:54:20 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	get_num(t_misc **amisc)
{
	int	res;

	res = 0;
	while (ft_isdigit(*(*amisc)->fmt_str))
	{
		res = (res * 10) + (*(*amisc)->fmt_str - '0');
		(*amisc)->fmt_str++;
	}
	return (res);
}

void		populate_width(t_misc **amisc, t_arg **ainfo)
{
	while (*(*amisc)->fmt_str)
	{
		if (ft_isdigit(*(*amisc)->fmt_str))
			(*ainfo)->width = get_num(amisc);
		else if (*(*amisc)->fmt_str == '*')
		{
			if (((*ainfo)->width = va_arg((*amisc)->ap, int)) < 0)
			{
				(*ainfo)->flags[MINUS_IDX] = 1;
				(*ainfo)->width *= -1;
			}
			(*amisc)->fmt_str++;
		}
		else
			break ;
	}
}

void		populate_precision(t_misc **amisc, t_arg **ainfo)
{
	while (*(*amisc)->fmt_str)
	{
		if (*(*amisc)->fmt_str == '.')
		{
			(*amisc)->fmt_str++;
			if (ft_isdigit(*(*amisc)->fmt_str))
				(*ainfo)->precis = get_num(amisc);
			else if (*(*amisc)->fmt_str == '*')
			{
				if (((*ainfo)->precis = va_arg((*amisc)->ap, int)) < 0)
					(*ainfo)->precis = -1;
				(*amisc)->fmt_str++;
			}
			else
				(*ainfo)->precis = 0;
		}
		else
			break ;
	}
}
