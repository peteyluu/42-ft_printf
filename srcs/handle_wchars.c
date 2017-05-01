#include "../incs/ft_printf.h"

static int	*get_idx_byte_cnt(wchar_t *ws, t_arg **ainfo)
{
	int	*idx_and_byte_cnt;
	int	precis_flag;
	int	tmp;

	precis_flag = 0;
	if ((*ainfo)->precis != -1)
		precis_flag = 1;
	idx_and_byte_cnt = (int*)malloc(sizeof(int) * 2);
	idx_and_byte_cnt[0] = 0;
	idx_and_byte_cnt[1] = 0;
	while (ws[idx_and_byte_cnt[0]])
	{
		tmp = get_byte_cnt(ws[idx_and_byte_cnt[0]]);
		if (precis_flag)
		{
			(*ainfo)->precis -= tmp;
			if ((*ainfo)->precis < 0)
			{
				(*ainfo)->precis = -1;
				break ;
			}
		}
		idx_and_byte_cnt[0]++;
		idx_and_byte_cnt[1] += tmp;
	}
	return (idx_and_byte_cnt);
}

static char	*handle_wstr(wchar_t *ws, t_arg **ainfo)
{
	int	i;
	int	*ret;
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

void		handle_bs_arg(t_data **aoutput, t_arg **ainfo, t_misc **amisc)
{
	wchar_t	*ws_arg;

	if (!(ws_arg = va_arg((*amisc)->ap, wchar_t*)))
		(*aoutput)->s_arg = "(null)";
	else
	{
		(*aoutput)->s_arg = handle_wstr(ws_arg, ainfo);
		(*aoutput)->free_arg = 1;
	}
}
