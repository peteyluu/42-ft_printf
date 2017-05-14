/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_va_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:55:12 by pluu              #+#    #+#             */
/*   Updated: 2017/05/08 13:58:46 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	is_oux(t_arg **ainfo)
{
	if ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'u' ||
		(*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
		return (1);
	return (0);
}

void		handle_va_arg(t_arg **ainfo, t_data **aout, t_misc **amisc)
{
	if ((*ainfo)->spec == 's' && (*ainfo)->leng == none)
		handle_s_arg(aout, amisc);
	else if ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i')
		handle_di_arg(ainfo, aout, amisc);
	else if (((*ainfo)->spec == 'c' || (*ainfo)->spec == '%') &&
			(*ainfo)->leng == none)
		handle_c_arg(ainfo, aout, amisc);
	else if ((*ainfo)->spec == 'D')
		handle_bd_arg(aout, amisc);
	else if ((*ainfo)->spec == 'O' || (*ainfo)->spec == 'U')
		handle_bou_arg(ainfo, aout, amisc);
	else if (is_oux(ainfo))
		handle_oux_arg(ainfo, aout, amisc);
	else if ((*ainfo)->spec == 'p')
		handle_p_arg(ainfo, aout, amisc);
	else if ((*ainfo)->spec == 'S' || ((*ainfo)->spec == 's' &&
			(*ainfo)->leng > 0))
		handle_bs_arg(ainfo, aout, amisc);
	else if ((*ainfo)->spec == 'C' || ((*ainfo)->spec == 'c' &&
			(*ainfo)->leng > 0))
		handle_bc_arg(aout, amisc);
	else if ((*ainfo)->spec == 'n')
		handle_n_arg(amisc);
	else
		handle_def_arg(aout, amisc);
}
