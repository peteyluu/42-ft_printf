#include "../incs/ft_printf.h"

static int	handle_left_prefix(t_arg **ainfo, t_data **aoutput)
{
	(*aoutput)->flag = find_flag(ainfo, aoutput);
	if ((*aoutput)->flag)
	{
		if ((*aoutput)->flag == 'x' || (*aoutput)->flag == 'X')
		{
			*(*aoutput)->presult++ = '0';
			*(*aoutput)->presult++ = (*aoutput)->flag;
			return (2);
		}
		else if (!is_hash_flag(ainfo) || (is_hash_flag(ainfo) && (*ainfo)->precis <= 1))
		{
			*(*aoutput)->presult++ = (*aoutput)->flag;
			return (1);
		}
	}
	return (0);
}

static int	handle_left_precis(t_arg **ainfo, t_data **aoutput, char c)
{
	int	precis;

	precis = 0;
	if ((*ainfo)->precis > (*aoutput)->len && ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i' ||(*ainfo)->spec == 'o'
		|| (*ainfo)->spec == 'O' || (*ainfo)->spec == 'u' || (*ainfo)->spec == 'U'
		|| (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X' || (*ainfo)->spec == 'D'))
	{
		precis = (*ainfo)->precis - (*aoutput)->len;
		ft_memset((*aoutput)->presult, c, precis);
		(*aoutput)->presult += precis;
	}
	return (precis);
}

void		handle_left_just(t_arg **ainfo, t_data **aoutput, char c)
{
	int	i;
	int	j;
	int	k;

	if ((*ainfo)->precis != -1 && (*ainfo)->precis != 0 && (*ainfo)->precis < (*aoutput)->len &&
		((*ainfo)->spec == 's' || (*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
		i = (*ainfo)->precis;
	else if ((*ainfo)->precis == 0 && (*ainfo)->precis < (*aoutput)->len && ft_strcmp((*aoutput)->s_arg, "0") == 0
		&& (((!is_hash_flag(ainfo) && ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'u' || (*ainfo)->spec == 'U')))
		|| (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
		i = 0;
	else	
		i = (*aoutput)->len;
	j = handle_left_prefix(ainfo, aoutput);
	k = handle_left_precis(ainfo, aoutput, c);
	ft_memcpy((*aoutput)->presult, (*aoutput)->s_arg, i);
	if (k)
		ft_memset((*aoutput)->presult + i, ' ', (*aoutput)->width - i - j - k);
	else
		ft_memset(((*aoutput)->presult) + i, c, (*aoutput)->width - i - j);
}
