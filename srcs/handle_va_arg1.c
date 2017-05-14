/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_va_arg1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:55:19 by pluu              #+#    #+#             */
/*   Updated: 2017/05/08 14:01:04 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	get_base(char spec)
{
	if (spec == 'o' || spec == 'O')
		return (8);
	else if (spec == 'x' || spec == 'X' || spec == 'p')
		return (16);
	return (10);
}

void		handle_p_arg(t_arg **ainfo, t_data **aout, t_misc **amisc)
{
	(*aout)->s_arg = uintmax_to_a_base(va_arg((*amisc)->ap, uintmax_t),
			16, (*ainfo)->spec);
	(*aout)->free_arg = 1;
}

void		handle_bou_arg(t_arg **ainfo, t_data **aout, t_misc **amisc)
{
	(*aout)->s_arg = uintmax_to_a_base((uintmax_t)va_arg((*amisc)->ap, long),
			get_base((*ainfo)->spec), (*ainfo)->spec);
	(*aout)->free_arg = 1;
}

void		handle_di_arg(t_arg **ainfo, t_data **aout, t_misc **amisc)
{
	if ((*ainfo)->leng == none)
		(*aout)->s_arg = ft_itoa(va_arg((*amisc)->ap, int));
	else if ((*ainfo)->leng == hh)
		(*aout)->s_arg = ft_itoa((int)(signed char)va_arg((*amisc)->ap, int));
	else if ((*ainfo)->leng == h)
		(*aout)->s_arg = ft_itoa((int)(short)va_arg((*amisc)->ap, int));
	else if ((*ainfo)->leng == ll)
		(*aout)->s_arg = intmax_to_a((intmax_t)va_arg((*amisc)->ap, long long));
	else if ((*ainfo)->leng == l)
		(*aout)->s_arg = intmax_to_a((intmax_t)va_arg((*amisc)->ap, long));
	else if ((*ainfo)->leng == j)
		(*aout)->s_arg = intmax_to_a(va_arg((*amisc)->ap, intmax_t));
	else
		(*aout)->s_arg = intmax_to_a((intmax_t)va_arg((*amisc)->ap, size_t));
	(*aout)->free_arg = 1;
}

void		handle_oux_arg(t_arg **ainfo, t_data **aout, t_misc **amisc)
{
	if ((*ainfo)->leng == none)
		(*aout)->s_arg = uintmax_to_a_base(
				(uintmax_t)(unsigned int)va_arg((*amisc)->ap, int),
				get_base((*ainfo)->spec), (*ainfo)->spec);
	else if ((*ainfo)->leng == hh)
		(*aout)->s_arg = uintmax_to_a_base(
				(uintmax_t)(unsigned char)va_arg((*amisc)->ap, int),
				get_base((*ainfo)->spec), (*ainfo)->spec);
	else if ((*ainfo)->leng == h)
		(*aout)->s_arg = uintmax_to_a_base(
				(uintmax_t)(unsigned short)va_arg((*amisc)->ap, int),
				get_base((*ainfo)->spec), (*ainfo)->spec);
	else if ((*ainfo)->leng == ll)
		(*aout)->s_arg = uintmax_to_a_base(
				(uintmax_t)va_arg((*amisc)->ap, unsigned long long),
				get_base((*ainfo)->spec), (*ainfo)->spec);
	else if ((*ainfo)->leng == l)
		(*aout)->s_arg = uintmax_to_a_base(
				(uintmax_t)va_arg((*amisc)->ap, unsigned long),
				get_base((*ainfo)->spec), (*ainfo)->spec);
	else
		(*aout)->s_arg = uintmax_to_a_base(va_arg((*amisc)->ap, uintmax_t),
				get_base((*ainfo)->spec), (*ainfo)->spec);
	(*aout)->free_arg = 1;
}
