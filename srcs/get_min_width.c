#include "../incs/ft_printf.h"

static void	get_s_precis(t_arg **ainfo, t_data **aoutput)
{
	if ((*ainfo)->width > (*ainfo)->precis)
		(*aoutput)->width = (*ainfo)->width;
	else if ((*ainfo)->precis >= (*ainfo)->width && (*ainfo)->precis <= (*aoutput)->len)
		(*aoutput)->width = (*ainfo)->precis;
	else if ((*ainfo)->precis > (*aoutput)->width && (*aoutput)->width < (*aoutput)->len) 
		(*aoutput)->width = (*aoutput)->len;
}

static void	get_di_precis(t_arg **ainfo, t_data **aoutput)
{
	if ((*ainfo)->precis == 0 && ft_strcmp((*aoutput)->s_arg, "0") == 0)
	{
		if ((*ainfo)->width == -1)
			(*aoutput)->width = 0;
	}
	else if ((*ainfo)->precis > (*aoutput)->width)
		(*aoutput)->width = (*ainfo)->precis;
}

static void	get_ouxdp_precis(t_arg **ainfo, t_data **aoutput)
{
	if ((*ainfo)->precis == 0 && ft_strcmp((*aoutput)->s_arg, "0") == 0 && (*ainfo)->width <= 0)
	{
		if (!is_hash_flag(ainfo) || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X' || (*ainfo)->spec == 'p')
			(*aoutput)->width = 0;
	}
	else if ((*ainfo)->precis > (*aoutput)->width)
		(*aoutput)->width = (*ainfo)->precis;
}

void		get_precis(t_arg **ainfo, t_data **aoutput)
{
	if ((*ainfo)->precis != -1)
	{
		if ((*ainfo)->spec == 's')
			get_s_precis(ainfo, aoutput);
		else if (((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
			get_di_precis(ainfo, aoutput);
		else if ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O' || (*ainfo)->spec == 'u' || (*ainfo)->spec == 'U'
			|| (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X' || (*ainfo)->spec == 'D' || (*ainfo)->spec == 'p')
			get_ouxdp_precis(ainfo, aoutput);
	}
}

void		get_min_width(t_arg **ainfo, t_data **aoutput)
{
	if ((*ainfo)->width != -1)
	{
		if ((*ainfo)->width < (*aoutput)->len && ((*ainfo)->precis != 0 || (*ainfo)->precis == 0))
			(*aoutput)->width = (*aoutput)->len;
		else
			(*aoutput)->width = (*ainfo)->width;
	}
	else
		(*aoutput)->width = (*aoutput)->len;
}
