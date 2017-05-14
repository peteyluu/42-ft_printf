/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:53:17 by pluu              #+#    #+#             */
/*   Updated: 2017/05/08 14:23:16 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static void	dispose_structs(t_arg **ainfo, t_data **aout, t_misc **amisc)
{
	ft_memdel((void**)&(*ainfo)->flags);
	ft_memdel((void**)ainfo);
	ft_memdel((void**)aout);
	free(*amisc);
}

static void	put_nbytes(char *s, size_t n)
{
	while (n--)
	{
		write(1, &*s, 1);
		s++;
	}
}

static int	get_output(t_arg **ainfo, t_data **aout, t_misc **amisc)
{
	(*amisc)->fmt_str++;
	init_output(aout);
	init_info(ainfo);
	populate_info(ainfo, amisc);
	if ((*ainfo)->spec == '\0' && (*ainfo)->width == -1)
		return (0);
	handle_va_arg(ainfo, aout, amisc);
	if ((*ainfo)->spec != 'n')
	{
		(*amisc)->ret += populate_result(ainfo, aout);
		put_nbytes((*aout)->result, (*aout)->width);
		ft_memdel((void**)&(*aout)->result);
		if ((*aout)->free_arg)
			ft_memdel((void**)&(*aout)->s_arg);
	}
	return (1);
}

static void	handle_printf(t_misc **amisc)
{
	t_arg	*info;
	t_data	*out;

	info = NULL;
	out = NULL;
	while (*(*amisc)->fmt_str)
	{
		if (*(*amisc)->fmt_str == '%' && *((*amisc)->fmt_str + 1) != '\0')
		{
			if (!get_output(&info, &out, amisc))
				continue ;
		}
		else if (*(*amisc)->fmt_str == '%' && *((*amisc)->fmt_str + 1) == '\0')
			break ;
		else
		{
			ft_putchar(*(*amisc)->fmt_str);
			(*amisc)->ret++;
		}
		(*amisc)->fmt_str++;
	}
	dispose_structs(&info, &out, amisc);
}

int			ft_printf(const char *format, ...)
{
	t_misc	*misc;

	init_misc(&misc, format);
	va_start(misc->ap, format);
	handle_printf(&misc);
	va_end(misc->ap);
	return (misc->ret);
}
