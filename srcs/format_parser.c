/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:53:59 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:54:01 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

void	populate_info(t_arg **ainfo, t_misc **amisc)
{
	populate_flags(amisc, ainfo);
	populate_width(amisc, ainfo);
	populate_precision(amisc, ainfo);
	populate_length(amisc, ainfo);
	populate_specifier(amisc, ainfo);
}
