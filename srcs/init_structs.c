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

void	init_output(t_data **aout)
{
	if (!*aout)
		*aout = (t_data*)malloc(sizeof(t_data));
	(*aout)->s_arg = NULL;
	(*aout)->free_arg = 0;
	(*aout)->len = 0;
	(*aout)->flag = 0;
	(*aout)->width = 0;
	(*aout)->result = NULL;
	(*aout)->presult = NULL;
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
