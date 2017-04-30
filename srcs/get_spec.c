#include "../incs/ft_printf.h"

static int	is_specifier(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
	    c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
	    c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

void		populate_specifier(char **aformat_cpy, t_arg **ainfo)
{
	while (**aformat_cpy)
	{
		if (is_specifier(**aformat_cpy))
		{
			(*ainfo)->spec = **aformat_cpy;
			break ;
	}
		else
		{
			if (is_flag(**aformat_cpy))
			{
				(*ainfo)->flags[get_idx_flag(**aformat_cpy)] = '1';
				(*aformat_cpy)++;
			}
			else
				break ;
		}
	}
}
