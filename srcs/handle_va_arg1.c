#include "../incs/ft_printf.h"

static int	get_base(char spec)
{
	if (spec == 'o' || spec == 'O')
		return (8);
	else if (spec == 'x' || spec == 'X' || spec == 'p')
		return (16);
	return (10);
}

void		handle_p_arg(t_data **aoutput, va_list ap, char spec)
{
	(*aoutput)->s_arg = uintmax_to_a_base(va_arg(ap, uintmax_t), 16, spec);
	(*aoutput)->free_arg = 1;
}

void		handle_bou_arg(t_data **aoutput, va_list ap, char spec)
{
	(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)va_arg(ap, long int), get_base(spec), spec);
	(*aoutput)->free_arg = 1;
}

void		handle_di_arg(t_data **aoutput, va_list ap, int leng)
{
	if (leng == hh)
		(*aoutput)->s_arg = ft_itoa((int)(signed char)va_arg(ap, int));
	else if (leng == h)
		(*aoutput)->s_arg = ft_itoa((int)(short int)va_arg(ap, int));
	else if (leng == ll)
		(*aoutput)->s_arg = intmax_to_a((intmax_t)va_arg(ap, long long int));
	else if (leng == l)
		(*aoutput)->s_arg = intmax_to_a((intmax_t)va_arg(ap, long int));
	else if (leng == j)
		(*aoutput)->s_arg = intmax_to_a(va_arg(ap, intmax_t));
	else if (leng == z)
		(*aoutput)->s_arg = intmax_to_a((intmax_t)va_arg(ap, size_t));
	else
		(*aoutput)->s_arg = ft_itoa(va_arg(ap, int));
	(*aoutput)->free_arg = 1;
}

void		handle_ouxX_arg(t_data **aoutput, va_list ap, int leng, char spec)
{
	if (leng == hh)
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)(unsigned char)va_arg(ap, int), get_base(spec), spec);
	else if (leng == h)
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)(unsigned short)va_arg(ap, int), get_base(spec), spec);
	else if (leng == ll)
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)va_arg(ap, unsigned long long), get_base(spec), spec);
	else if (leng == l)
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)va_arg(ap, unsigned long), get_base(spec), spec);
	else if (leng == j || leng == z)
		(*aoutput)->s_arg = uintmax_to_a_base(va_arg(ap, uintmax_t), get_base(spec), spec);
	else
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)(unsigned int)va_arg(ap, int), get_base(spec), spec);
	(*aoutput)->free_arg = 1;
}
