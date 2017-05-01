#include "../incs/ft_printf.h"

void	populate_info(t_arg **ainfo, t_misc **amisc)
{
	populate_flags(amisc, ainfo);
	populate_width(amisc, ainfo);
	populate_precision(amisc, ainfo);
	populate_length(amisc, ainfo);
	populate_specifier(amisc, ainfo);
}
