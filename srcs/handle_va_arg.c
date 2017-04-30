#include "../incs/ft_printf.h"

void	handle_va_arg(t_arg **ainfo, t_data **aoutput, char **aformat_cpy, va_list ap)
{
	char	spec;
	int	leng;

	spec = (*ainfo)->spec;
	leng = (*ainfo)->leng;
	if (spec == 's' && leng == none)
		handle_s_arg(aoutput, ap);
	else if (spec == 'd' || spec == 'i')
		handle_di_arg(aoutput, ap, leng);
	else if ((spec == 'c' || spec == '%') && leng == none)
		handle_c_arg(aoutput, ap, spec);
	else if (spec == 'D')
		handle_bd_arg(aoutput, ap);
	else if (spec == 'O' || spec == 'U')
		handle_bou_arg(aoutput, ap, spec);
	else if (spec == 'o' || spec == 'u' || spec == 'x' || spec == 'X')
		handle_ouxX_arg(aoutput, ap, leng, spec);
	else if (spec == 'p')
		handle_p_arg(aoutput, ap, spec);
	else if (spec == 'S' || (spec == 's' && leng > 0))
		handle_bs_arg(aoutput, ainfo, ap);
	else if (spec == 'C' || (spec == 'c' && leng > 0))
		handle_bc_arg(aoutput, ap);
	else
		handle_def_arg(aoutput, aformat_cpy);
}
