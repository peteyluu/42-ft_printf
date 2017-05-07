/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:53:27 by pluu              #+#    #+#             */
/*   Updated: 2017/05/07 15:53:28 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

void	init_output(t_data **aoutput)
{
	if (!*aoutput)
		*aoutput = (t_data*)malloc(sizeof(t_data));
	(*aoutput)->s_arg = NULL;
	(*aoutput)->free_arg = 0;
	(*aoutput)->len = 0;
	(*aoutput)->flag = 0;
	(*aoutput)->width = 0;
	(*aoutput)->result = NULL;
	(*aoutput)->presult = NULL;
}

void	init_info(t_arg **ainfo)
{
	if (!*ainfo)
		*ainfo = (t_arg*)malloc(sizeof(t_arg));
	else
		ft_memdel((void**)&(*ainfo)->flags);
	(*ainfo)->flags = ft_strnew(NUM_FLAGS);
	(*ainfo)->width = -1;
	(*ainfo)->precis = -1;
	(*ainfo)->leng = none;
	(*ainfo)->spec = '\0';
}

void	init_misc(t_misc **amisc, const char *format)
{
	*amisc = (t_misc*)malloc(sizeof(t_misc));
	(*amisc)->ret = 0;
	(*amisc)->fmt_str = (char*)format;
}
