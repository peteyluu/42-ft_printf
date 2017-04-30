#include "../incs/ft_printf.h"

static int	get_num(char **aformat_cpy)
{
	int	res;

	res = 0;
	while (ft_isdigit(**aformat_cpy))
	{
		res = (res * 10) + ((**aformat_cpy) - '0');
		(*aformat_cpy)++;
	}
	return (res);
}

void		populate_width(char **aformat_cpy, t_arg **ainfo, va_list ap)
{
	while (**aformat_cpy)
	{
		if (ft_isdigit(**aformat_cpy))
			(*ainfo)->width = get_num(aformat_cpy);
		else if (**aformat_cpy == '*')
		{
			if (((*ainfo)->width = va_arg(ap, int)) < 0)
			{
				(*ainfo)->flags[MINUS_IDX] = 1;
				(*ainfo)->width *= -1;
			}
			(*aformat_cpy)++;
		}
		else
			break ;
	}
}

void		populate_precision(char **aformat_cpy, t_arg **ainfo, va_list ap)
{
	while (**aformat_cpy)
	{
		if (**aformat_cpy == '.')
		{
			(*aformat_cpy)++;
			if (ft_isdigit(**aformat_cpy))
				(*ainfo)->precis = get_num(aformat_cpy);
			else if (**aformat_cpy == '*')
			{
				if (((*ainfo)->precis = va_arg(ap, int)) < 0)
					(*ainfo)->precis = -1;
				(*aformat_cpy)++;
			}
			else
				(*ainfo)->precis = 0;
		}
		else
			break ;
	}
}
