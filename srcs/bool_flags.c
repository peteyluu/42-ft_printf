/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:52:36 by pluu              #+#    #+#             */
/*   Updated: 2017/05/08 14:32:48 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

int	is_hash_flag(t_arg **ainfo)
{
	return ((*ainfo)->flags[HASH_IDX] ? 1 : 0);
}

int	is_space_flag(t_arg **ainfo)
{
	return ((*ainfo)->flags[SPACE_IDX] ? 1 : 0);
}

int	is_zero_flag(t_arg **ainfo)
{
	return ((*ainfo)->flags[ZERO_IDX] ? 1 : 0);
}

int	is_plus_flag(t_arg **ainfo)
{
	if ((*ainfo)->flags[PLUS_IDX] && ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i' || (*ainfo)->spec == 'D' || (*ainfo)->spec == 'p'))
		return (1);
	return (0);
}

int	is_left_just(t_arg **ainfo)
{
	return ((*ainfo)->flags[MINUS_IDX] ? 1 : 0);
}
