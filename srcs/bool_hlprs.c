/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_hlprs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:53:49 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:53:51 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

int	is_valid_width(t_arg **ainfo, t_data **aoutput)
{
	if ((*aoutput)->width > (*ainfo)->precis && (*ainfo)->precis != -1 && (*aoutput)->width > (*aoutput)->len)
		return (1);
	return (0);
}

int	is_valid_space_flag(t_arg **ainfo, t_data **aoutput)
{
	if (((((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i') && (*(*aoutput)->s_arg == '-'
		|| is_plus_flag(ainfo))) || (*ainfo)->spec == 'u' || (*ainfo)->spec == 'U'
		|| (*ainfo)->spec == 'c' || (*ainfo)->spec == 'o' || (*ainfo)->spec == 'x'
		|| (*ainfo)->spec == 'X' || (*ainfo)->spec == '%' || (*ainfo)->spec == 's'
		|| (*ainfo)->spec == 'C' || (*ainfo)->spec == 'S') || (*ainfo)->spec == 'p')
		return (0);
	return (1);
}
