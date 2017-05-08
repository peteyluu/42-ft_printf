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

void	handle_va_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc)
{
	if ((*ainfo)->spec == 's' && (*ainfo)->leng == none)
		handle_s_arg(aoutput, amisc);
	else if ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i')
		handle_di_arg(ainfo, aoutput, amisc);
	else if (((*ainfo)->spec == 'c' || (*ainfo)->spec == '%') && (*ainfo)->leng == none)
		handle_c_arg(ainfo, aoutput, amisc);
	else if ((*ainfo)->spec == 'D')
		handle_bd_arg(aoutput, amisc);
	else if ((*ainfo)->spec == 'O' || (*ainfo)->spec == 'U')
		handle_bou_arg(ainfo, aoutput, amisc);
	else if ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'u' || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
		handle_ouxX_arg(ainfo, aoutput, amisc);
	else if ((*ainfo)->spec == 'p')
		handle_p_arg(ainfo, aoutput, amisc);
	else if ((*ainfo)->spec == 'S' || ((*ainfo)->spec == 's' && (*ainfo)->leng > 0))
		handle_bs_arg(ainfo, aoutput, amisc);
	else if ((*ainfo)->spec == 'C' || ((*ainfo)->spec == 'c' && (*ainfo)->leng > 0))
		handle_bc_arg(aoutput, amisc);
	else if ((*ainfo)->spec == 'n')
		handle_n_arg(amisc);
	else
		handle_def_arg(aoutput, amisc);
}
