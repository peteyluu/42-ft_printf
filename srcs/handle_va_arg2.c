/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_va_arg2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:55:24 by pluu              #+#    #+#             */
/*   Updated: 2017/05/08 13:56:11 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

void	handle_s_arg(t_data **aoutput, t_misc **amisc)
{
	if (!((*aoutput)->s_arg = va_arg((*amisc)->ap, char*)))
		(*aoutput)->s_arg = "(null)";
}

void	handle_c_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc)
{
	(*aoutput)->s_arg = ft_strnew(1);
	*(*aoutput)->s_arg = ((*ainfo)->spec == 'c' ? va_arg((*amisc)->ap, int) : '%');
	(*aoutput)->free_arg = 1;
}

void	handle_bd_arg(t_data **aoutput, t_misc **amisc)
{
	(*aoutput)->s_arg = intmax_to_a((intmax_t)va_arg((*amisc)->ap, long int));
	(*aoutput)->free_arg = 1;
}

void	handle_def_arg(t_data **aoutput, t_misc **amisc)
{
	(*aoutput)->s_arg = ft_strnew(1);
	*(*aoutput)->s_arg = *(*amisc)->fmt_str;
	(*aoutput)->free_arg = 1;
}

void	handle_n_arg(t_misc **amisc)
{
	int	*pi;

	pi = va_arg((*amisc)->ap, int*);
	*pi = (*amisc)->ret;
}
