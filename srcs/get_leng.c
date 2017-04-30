#include "../incs/ft_printf.h"

static int	is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

static int	get_length(char **aformat_cpy)
{
	if (**aformat_cpy == 'h' && *(*aformat_cpy + 1) == 'h')
		return (hh);
	else if (**aformat_cpy == 'l' && *(*aformat_cpy + 1) == 'l')
		return (ll);
	else if (**aformat_cpy == 'h')
		return (h);
	else if (**aformat_cpy == 'l')
		return (l);
	else if (**aformat_cpy == 'j')
		return (j);
	else if (**aformat_cpy == 'z')
		return (z);
	return (0);
}

void		populate_length(char **aformat_cpy, t_arg **ainfo)
{
	int	tmp;

	while (**aformat_cpy)
	{
		if (is_length(**aformat_cpy))
		{
			tmp = get_length(aformat_cpy);
			if (tmp > (*ainfo)->leng)
				(*ainfo)->leng = tmp;
			if (tmp == hh || tmp == ll)
				(*aformat_cpy)++;
			(*aformat_cpy)++;
		}
		else
			break ;
	}
}
