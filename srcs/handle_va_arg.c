#include "../incs/ft_printf.h"

void	handle_n_arg(t_misc **amisc)
{
	int		*pi;
	//signed char	*psc;
	//short int	*psi;
	//long int	*pli;
	//long long int	*plli;
	//intmax_t	*pimax;
	//size_t		*psz;

	//if ((*ainfo)->leng == none)
	//{
	//	pi = va_arg((*amisc)->ap, int*);
	//	*pi = (*amisc)->ret;
	//}
	//else if ((*ainfo)->leng == hh)
	//{
	//	psc = va_arg((*amisc)->ap, signed char*);
	//	*psc = (*amisc)->ret;
	//}
	//else if ((*ainfo)->leng == h)
	//{
	//	psi = va_arg((*amisc)->ap, short int*);
	//	*psi = (*amisc)->ret;
	//}
	//else if ((*ainfo)->leng == l)
	//{
	//	pli = va_arg((*amisc)->ap, long int*);
	//	*pli = (*amisc)->ret;
	//}
	//else if ((*ainfo)->leng == ll)
	//{
	//	plli = va_arg((*amisc)->ap, long long int*);
	//	*plli = (*amisc)->ret;
	//}
	//else if ((*ainfo)->leng == j)
	//{
	//	pimax = va_arg((*amisc)->ap, intmax_t*);
	//	*pimax = (*amisc)->ret;
	//}
	//else
	//{
	//	psz = va_arg((*amisc)->ap, size_t*);
	//	*psz = (*amisc)->ret;
	//}
	pi = va_arg((*amisc)->ap, int*);
	*pi = (*amisc)->ret;
}

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
	else if (spec == 'n')
		handle_n_arg(amisc);
	else
		handle_def_arg(aoutput, amisc);
}
