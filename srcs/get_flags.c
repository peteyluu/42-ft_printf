/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:54:09 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:54:11 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

int	get_idx_flag(char c)
{
	if (c == '-')
		return (MINUS_IDX);
	else if (c == '+')
		return (PLUS_IDX);
	else if (c == ' ')
		return (SPACE_IDX);
	else if (c == '0')
		return (ZERO_IDX);
	else
		return (HASH_IDX);
}

int	is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '0' || c == '#')
		return (1);
	return (0);
}

void	populate_flags(t_misc **amisc, t_arg **ainfo)
{
	while (*(*amisc)->fmt_str)
	{
		if (is_flag(*(*amisc)->fmt_str))
			(*ainfo)->flags[get_idx_flag(*(*amisc)->fmt_str)] = '1';
		else
			break ;
		(*amisc)->fmt_str++;
	}
}
