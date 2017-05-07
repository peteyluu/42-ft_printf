#include "../incs/ft_printf.h"

static int	is_specifier(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
	    c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
	    c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%' || c == 'n')
		return (1);
	return (0);
}

void		populate_specifier(t_misc **amisc, t_arg **ainfo)
{
	while (*(*amisc)->fmt_str)
	{
		if (is_specifier(*(*amisc)->fmt_str))
		{
			(*ainfo)->spec = *(*amisc)->fmt_str;
			break ;
		}
		else
		{
			if (is_flag(*(*amisc)->fmt_str))
			{
				(*ainfo)->flags[get_idx_flag(*(*amisc)->fmt_str)] = '1';
				(*amisc)->fmt_str++;
			}
			else
				break ;
		}
	}
}
