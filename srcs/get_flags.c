#include "../incs/ft_printf.h"

int	get_idx_flag(char c)
{
	if (c == '-')
		return (MINUS_IDX);
	else if (c == '+')
		return (PLUS_IDX);
	else if (c == ' ')
		return (SPACE_IDX);
	else if (c == '0')
		return (ZERO_IDX);
	else
		return (HASH_IDX);
}

int	is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '0' || c == '#')
		return (1);
	return (0);
}

void	populate_flags(char **aformat_cpy, t_arg **ainfo)
{
	while (**aformat_cpy)
	{
		if (is_flag(**aformat_cpy))
			(*ainfo)->flags[get_idx_flag(**aformat_cpy)] = '1';
		else
			break ;
		(*aformat_cpy)++;
	}
}
