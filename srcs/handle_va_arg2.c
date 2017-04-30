#include "../incs/ft_printf.h"

void	handle_s_arg(t_data **aoutput, va_list ap)
{
	if (!((*aoutput)->s_arg = va_arg(ap, char*)))
		(*aoutput)->s_arg = "(null)";
}

void	handle_c_arg(t_data **aoutput, va_list ap, char spec)
{
	(*aoutput)->s_arg = ft_strnew(1);
	*(*aoutput)->s_arg = (spec == 'c' ? va_arg(ap, int) : '%');
	(*aoutput)->free_arg = 1;
}

void	handle_bd_arg(t_data **aoutput, va_list ap)
{
	(*aoutput)->s_arg = intmax_to_a((intmax_t)va_arg(ap, long int));
	(*aoutput)->free_arg = 1;
}

void	handle_def_arg(t_data **aoutput, char **aformat_cpy)
{
	(*aoutput)->s_arg = ft_strnew(1);
	*(*aoutput)->s_arg = **aformat_cpy++;
	(*aoutput)->free_arg = 1;
}
