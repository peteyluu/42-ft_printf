#include "../incs/ft_printf.h"

static void	init_output(t_data **aoutput)
{
	if (!*aoutput)
		*aoutput = (t_data*)malloc(sizeof(t_data));
	(*aoutput)->s_arg = NULL;
	(*aoutput)->free_arg = 0;
	(*aoutput)->len = 0;
	(*aoutput)->flag = 0;
	(*aoutput)->width = 0;
	(*aoutput)->result = NULL;
	(*aoutput)->presult = NULL;
}

static void	init_info(t_arg **ainfo)
{
	if (!*ainfo)
		*ainfo = (t_arg*)malloc(sizeof(t_arg));
	else
		ft_memdel((void**)&(*ainfo)->flags);
	(*ainfo)->flags = ft_strnew(NUM_FLAGS);
	(*ainfo)->width = -1;
	(*ainfo)->precis = -1;
	(*ainfo)->leng = none;
	(*ainfo)->spec = '\0';
}

static void	dispose_structs(t_arg **ainfo, t_data **aoutput)
{
	ft_memdel((void**)&(*ainfo)->flags);
	ft_memdel((void**)ainfo);
	ft_memdel((void**)aoutput);
}

static void	ft_putstr_nbytes(char *s, size_t n)
{
	while (n--)
	{
		write(1, &*s, 1);
		s++;
	}
}

int		ft_printf(const char *format, ...)
{
	char	*fmt_cpy;
	int	ret;
	va_list	ap;
	t_arg	*info;
	t_data	*output;

	ret = 0;
	info = NULL;
	output = NULL;
	fmt_cpy = (char*)format;
	va_start(ap, format);
	while (*fmt_cpy)
	{
		if (*fmt_cpy == '%' && *(fmt_cpy + 1) != '\0')
		{
			fmt_cpy++;
			init_output(&output);
			init_info(&info);
			populate_info(&fmt_cpy, &info, ap);
			if (info->spec == '\0' && info->width == -1)
				continue ;
			handle_va_arg(&info, &output, &fmt_cpy, ap);
			ret += populate_result(&info, &output);
			ft_putstr_nbytes(output->result, output->width);
			ft_memdel((void**)&output->result);
			if (output->free_arg)
				ft_memdel((void**)&output->s_arg);
		}
		else if (*fmt_cpy == '%' && *(fmt_cpy + 1) == '\0')
			break ;
		else
		{
			ft_putchar(*fmt_cpy);
			ret++;
		}
		fmt_cpy++;
	}
	dispose_structs(&info, &output);
	va_end(ap);
	return (ret);
}
