#include "../incs/ft_printf.h"

static void	dispose_structs(t_arg **ainfo, t_data **aoutput, t_misc **amisc)
{
	ft_memdel((void**)&(*ainfo)->flags);
	ft_memdel((void**)ainfo);
	ft_memdel((void**)aoutput);
	free(*amisc);
}

static void	put_nbytes(char *s, size_t n)
{
	while (n--)
	{
		write(1, &*s, 1);
		s++;
	}
}

static int	get_output(t_arg **ainfo, t_data **aoutput, t_misc **amisc)
{
	(*amisc)->fmt_str++;
	init_output(aoutput);
	init_info(ainfo);
	populate_info(ainfo, amisc);
	if ((*ainfo)->spec == '\0' && (*ainfo)->width == -1)
		return (0);
	handle_va_arg(ainfo, aoutput, amisc);
	if ((*ainfo)->spec != 'n')
	{
		(*amisc)->ret += populate_result(ainfo, aoutput);
		put_nbytes((*aoutput)->result, (*aoutput)->width);
		ft_memdel((void**)&(*aoutput)->result);
		if ((*aoutput)->free_arg)
			ft_memdel((void**)&(*aoutput)->s_arg);
	}
	return (1);
}

int		ft_printf(const char *format, ...)
{
	t_arg	*info;
	t_data	*output;
	t_misc	*misc;

	info = NULL;
	output = NULL;
	init_misc(&misc, format);
	va_start(misc->ap, format);
	while (*misc->fmt_str)
	{
		if (*misc->fmt_str == '%' && *(misc->fmt_str + 1) != '\0')
		{
			if (!get_output(&info, &output, &misc))
				continue ;
		}
		else if (*misc->fmt_str == '%' && *(misc->fmt_str + 1) == '\0')
			break ;
		else
		{
			ft_putchar(*misc->fmt_str);
			misc->ret++;
		}
		misc->fmt_str++;
	}
	dispose_structs(&info, &output, &misc);
	va_end(misc->ap);
	return (misc->ret);
}
