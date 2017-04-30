#include "../incs/ft_printf.h"

void	populate_info(char **aformat_cpy, t_arg **ainfo, va_list ap)
{
	populate_flags(aformat_cpy, ainfo);
	populate_width(aformat_cpy, ainfo, ap);
	populate_precision(aformat_cpy, ainfo, ap);
	populate_length(aformat_cpy, ainfo);
	populate_specifier(aformat_cpy, ainfo);
}
