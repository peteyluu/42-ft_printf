#include "../incs/ft_printf.h"

static int	is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

static int	get_length(t_misc **amisc)
{
	if (*(*amisc)->fmt_str == 'h' && *((*amisc)->fmt_str + 1) == 'h')
		return (hh);
	else if (*(*amisc)->fmt_str == 'l' && *((*amisc)->fmt_str + 1) == 'l')
		return (ll);
	else if (*(*amisc)->fmt_str == 'h')
		return (h);
	else if (*(*amisc)->fmt_str == 'l')
		return (l);
	else if (*(*amisc)->fmt_str == 'j')
		return (j);
	else if (*(*amisc)->fmt_str == 'z')
		return (z);
	return (0);
}

void		populate_length(t_misc **amisc, t_arg **ainfo)
{
	int	tmp;

	while (*(*amisc)->fmt_str)
	{
		if (is_length(*(*amisc)->fmt_str))
		{
			tmp = get_length(amisc);
			if (tmp > (*ainfo)->leng)
				(*ainfo)->leng = tmp;
			if (tmp == hh || tmp == ll)
				(*amisc)->fmt_str++;
			(*amisc)->fmt_str++;
		}
		else
			break ;
	}
}
