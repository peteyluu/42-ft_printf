/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wchars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:55:34 by pluu              #+#    #+#             */
/*   Updated: 2017/05/08 13:58:37 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static int	*get_idx_byte_cnt(wchar_t *ws, t_arg **ainfo)
{
	int	*idx_and_byte_cnt;
	int	tmp[2];

	tmp[1] = 0;
	if ((*ainfo)->precis != -1)
		tmp[1] = 1;
	idx_and_byte_cnt = (int*)malloc(sizeof(int) * 2);
	idx_and_byte_cnt[0] = 0;
	idx_and_byte_cnt[1] = 0;
	while (ws[idx_and_byte_cnt[0]])
	{
		tmp[0] = get_byte_cnt(ws[idx_and_byte_cnt[0]]);
		if (tmp[1])
		{
			(*ainfo)->precis -= tmp[0];
			if ((*ainfo)->precis < 0)
			{
				(*ainfo)->precis = -1;
				break ;
			}
		}
		idx_and_byte_cnt[0]++;
		idx_and_byte_cnt[1] += tmp[0];
	}
	return (idx_and_byte_cnt);
}

static char	*handle_wstr(wchar_t *ws, t_arg **ainfo)
{
	int		i;
	int		*ret;
	char	*s;
	char	*ps;

	ret = get_idx_byte_cnt(ws, ainfo);
	s = ft_strnew(ret[1]);
	ps = s;
	i = 0;
	while (i < ret[0])
		unicode_to_utf8(ws[i++], &s);
	ft_memdel((void**)&ret);
	return (ps);
}

void		handle_bs_arg(t_arg **ainfo, t_data **aout, t_misc **amisc)
{
	wchar_t	*ws_arg;

	if (!(ws_arg = va_arg((*amisc)->ap, wchar_t*)))
		(*aout)->s_arg = "(null)";
	else
	{
		(*aout)->s_arg = handle_wstr(ws_arg, ainfo);
		(*aout)->free_arg = 1;
	}
}
