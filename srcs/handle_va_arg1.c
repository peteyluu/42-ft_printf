/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_va_arg1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:55:19 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:55:20 by pluu             ###   ########.fr       */
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

void		handle_p_arg(t_data **aoutput, t_misc **amisc, char spec)
{
	(*aoutput)->s_arg = uintmax_to_a_base(va_arg((*amisc)->ap, uintmax_t), 16, spec);
	(*aoutput)->free_arg = 1;
}

void		handle_bou_arg(t_data **aoutput, t_misc **amisc, char spec)
{
	(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)va_arg((*amisc)->ap, long int), get_base(spec), spec);
	(*aoutput)->free_arg = 1;
}

void		handle_di_arg(t_data **aoutput, t_misc **amisc, int leng)
{
	if (leng == none)
		(*aoutput)->s_arg = ft_itoa(va_arg((*amisc)->ap, int));
	else if (leng == hh)
		(*aoutput)->s_arg = ft_itoa((int)(signed char)va_arg((*amisc)->ap, int));
	else if (leng == h)
		(*aoutput)->s_arg = ft_itoa((int)(short int)va_arg((*amisc)->ap, int));
	else if (leng == ll)
		(*aoutput)->s_arg = intmax_to_a((intmax_t)va_arg((*amisc)->ap, long long int));
	else if (leng == l)
		(*aoutput)->s_arg = intmax_to_a((intmax_t)va_arg((*amisc)->ap, long int));
	else if (leng == j)
		(*aoutput)->s_arg = intmax_to_a(va_arg((*amisc)->ap, intmax_t));
	else
		(*aoutput)->s_arg = intmax_to_a((intmax_t)va_arg((*amisc)->ap, size_t));
	(*aoutput)->free_arg = 1;
}

void		handle_ouxX_arg(t_data **aoutput, t_misc **amisc, int leng, char spec)
{
	if (leng == none)
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)(unsigned int)va_arg((*amisc)->ap, int), get_base(spec), spec);
	else if (leng == hh)
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)(unsigned char)va_arg((*amisc)->ap, int), get_base(spec), spec);
	else if (leng == h)
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)(unsigned short)va_arg((*amisc)->ap, int), get_base(spec), spec);
	else if (leng == ll)
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)va_arg((*amisc)->ap, unsigned long long), get_base(spec), spec);
	else if (leng == l)
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)va_arg((*amisc)->ap, unsigned long), get_base(spec), spec);
	else
		(*aoutput)->s_arg = uintmax_to_a_base(va_arg((*amisc)->ap, uintmax_t), get_base(spec), spec);
	(*aoutput)->free_arg = 1;
}
