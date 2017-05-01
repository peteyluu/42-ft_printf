#include "../incs/ft_printf.h"

void	handle_va_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc)
{
	char	spec;
	int	leng;

	spec = (*ainfo)->spec;
	leng = (*ainfo)->leng;
	if (spec == 's' && leng == none)
		handle_s_arg(aoutput, amisc);
	else if (spec == 'd' || spec == 'i')
		handle_di_arg(aoutput, amisc, leng);
	else if ((spec == 'c' || spec == '%') && leng == none)
		handle_c_arg(aoutput, amisc, spec);
	else if (spec == 'D')
		handle_bd_arg(aoutput, amisc);
	else if (spec == 'O' || spec == 'U')
		handle_bou_arg(aoutput, amisc, spec);
	else if (spec == 'o' || spec == 'u' || spec == 'x' || spec == 'X')
		handle_ouxX_arg(aoutput, amisc, leng, spec);
	else if (spec == 'p')
		handle_p_arg(aoutput, amisc, spec);
	else if (spec == 'S' || (spec == 's' && leng > 0))
		handle_bs_arg(aoutput, ainfo, amisc);
	else if (spec == 'C' || (spec == 'c' && leng > 0))
		handle_bc_arg(aoutput, amisc);
	else
		handle_def_arg(aoutput, amisc);
}
