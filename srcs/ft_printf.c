#include "../incs/ft_printf.h"

int	ft_printf(const char *format, ...)
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

void	ft_putstr_nbytes(char *s, size_t n)
{
	while (n--)
	{
		write(1, &*s, 1);
		s++;
	}
}

void	dispose_structs(t_arg **ainfo, t_data **aoutput)
{
	ft_memdel((void**)&(*ainfo)->flags);
	ft_memdel((void**)ainfo);
	ft_memdel((void**)aoutput);
}

void	handle_va_arg(t_arg **ainfo, t_data **aoutput, char **aformat_cpy, va_list ap)
{
	char	spec;
	int	leng;
	wchar_t *ws_arg;

	spec = (*ainfo)->spec;
	leng = (*ainfo)->leng;
	if (spec == 's' && leng == none)
	{
		if (!((*aoutput)->s_arg = va_arg(ap, char*)))
			(*aoutput)->s_arg = "(null)";
	}
	else if (spec == 'd' || spec == 'i')
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
	else if ((spec == 'c' || spec == '%') && leng == none)
	{
		(*aoutput)->s_arg = ft_strnew(1);
		*(*aoutput)->s_arg = (spec == 'c' ? va_arg(ap, int) : '%');
		(*aoutput)->free_arg = 1;
	}
	else if (spec == 'D')
	{
		(*aoutput)->s_arg = intmax_to_a((intmax_t)va_arg(ap, long int));
		(*aoutput)->free_arg = 1;
	}
	else if (spec == 'O' || spec == 'U')
	{
		(*aoutput)->s_arg = uintmax_to_a_base((uintmax_t)va_arg(ap, long int), get_base(spec), spec);
		(*aoutput)->free_arg = 1;
	}
	else if (spec == 'o' || spec == 'u' || spec == 'x' || spec == 'X')
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
	else if (spec == 'p')
	{
		(*aoutput)->s_arg = uintmax_to_a_base(va_arg(ap, uintmax_t), 16, spec);
		(*aoutput)->free_arg = 1;
	}
	else if (spec == 'S' || (spec == 's' && leng > 0))
	{
		if (!(ws_arg = va_arg(ap, wchar_t*)))
			(*aoutput)->s_arg = "(null)";
		else
		{
			(*aoutput)->s_arg = handle_wstr(ws_arg, ainfo);
			(*aoutput)->free_arg = 1;
		}
	}
	else if (spec == 'C' || (spec == 'c' && leng > 0))
	{
		//(*aoutput)->s_arg = ft_strnew(1);
		//*(*aoutput)->s_arg = va_arg(ap, int);
		(*aoutput)->s_arg = handle_wch(va_arg(ap, wchar_t));
		(*aoutput)->free_arg = 1;
	}
	else
	{
		(*aoutput)->s_arg = ft_strnew(1);
		*(*aoutput)->s_arg = **aformat_cpy++;
		(*aoutput)->free_arg = 1;
	}
}

void	unicode_to_utf8(wchar_t c, char **as)
{
	if (c<(1<<7))// 7 bit Unicode encoded as plain ascii
	{
		*(*as)++ = (unsigned char)(c);
	}
	else if (c<(1<<11))// 11 bit Unicode encoded in 2 UTF-8 bytes
	{
		*(*as)++ = (unsigned char)((c>>6)|0xC0);
		*(*as)++ = (unsigned char)((c&0x3F)|0x80);
	}
	else if (c<(1<<16))// 16 bit Unicode encoded in 3 UTF-8 bytes
	{
		*(*as)++ = (unsigned char)(((c>>12))|0xE0);
		*(*as)++ =  (unsigned char)(((c>>6)&0x3F)|0x80);
		*(*as)++ =  (unsigned char)((c&0x3F)|0x80);
	}
	else if (c<(1<<21))// 21 bit Unicode encoded in 4 UTF-8 bytes
	{
		*(*as)++ = (unsigned char)(((c>>18))|0xF0);
		*(*as)++ = (unsigned char)(((c>>12)&0x3F)|0x80);
		*(*as)++ = (unsigned char)(((c>>6)&0x3F)|0x80);
		*(*as)++ = (unsigned char)((c&0x3F)|0x80);
	}
}

int 	get_byte_cnt(wchar_t wc)
{
	if (wc < 128)
		return (1);
	else if (wc < 2048)
		return (2);
	else if (wc < 65536)
		return (3);
	else
		return (4);
}

char	*handle_wch(wchar_t wc)
{
	int	num_bytes;
	char	*s;
	char	*ps;

	num_bytes = get_byte_cnt(wc);
	s = ft_strnew(num_bytes);
	ps = s;
	unicode_to_utf8(wc, &s);
	return (ps);
}

char	*handle_wstr(wchar_t *ws, t_arg **ainfo)
{
	int	num_bytes;
	char	*s;
	char	*ps;
	int	i;
	int	cnt;
	int	tmp;
	int	precis_flag;

	precis_flag = 0;
	if ((*ainfo)->precis != -1)
		precis_flag = 1;
	num_bytes = 0;
	cnt = 0;
	i = 0;
	while (ws[i])
	{
		tmp = get_byte_cnt(ws[i++]);
		if (precis_flag)
		{
			(*ainfo)->precis -= tmp;
			if ((*ainfo)->precis < 0)
			{
				(*ainfo)->precis = -1;
				break ;
			}
		}
		num_bytes += tmp;
		cnt++;
	}
	s = ft_strnew(num_bytes);
	ps = s;
	i = 0;
	while (i < cnt)
		unicode_to_utf8(ws[i++], &s);
	return (ps);
}

int	populate_result(t_arg **ainfo, t_data **aoutput)
{
	(*aoutput)->len = ft_strlen((*aoutput)->s_arg);	
	if ((*aoutput)->len == 0 && ((*ainfo)->spec == 'c' || (*ainfo)->spec == 'C'))
		(*aoutput)->len = 1;
	get_min_width(ainfo, aoutput);
	get_precision(ainfo, aoutput);
	update_result(ainfo, aoutput);
	if (is_width_pad(ainfo, (*aoutput)->len))
		width_padding(ainfo, aoutput);
	else
		pop_res_hlpr(ainfo, aoutput);
	return ((*aoutput)->width);
}

void	pop_res_hlpr(t_arg **ainfo, t_data **aoutput)
{
	int	 offset_width;

	offset_width = 0;
	// delete line 266?
	if ((*ainfo)->flags[PLUS_IDX] && *(*aoutput)->s_arg != '-' &&
		((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i' || (*ainfo)->spec == 'D'))
	{
		*(*aoutput)->presult++ = '+';
		offset_width++;
	}
	// 4-18-17 -> added (*ainfo)->spec != '%'
	// deleted `#is_valid_space_flag(ainfo, aoutput))???
	if ((*ainfo)->spec != 'p' && (*ainfo)->flags[SPACE_IDX] && is_valid_space_flag(ainfo, aoutput))
	{
		*(*aoutput)->presult++ = ' ';
		offset_width++;
	}
	if (is_hash_flag(ainfo) && ft_strcmp((*aoutput)->s_arg, "0") != 0 &&
		((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O' || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
	{
		*(*aoutput)->presult++ = '0';
		offset_width++;
		if ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
		{
			*(*aoutput)->presult++ = (*ainfo)->spec;
			offset_width++;
		}
	}
	if ((*ainfo)->spec == 'p')
	{
		*(*aoutput)->presult++ = '0';
		*(*aoutput)->presult++ = 'x';
		offset_width += 2;
	}
	ft_memcpy(((*aoutput)->presult), (*aoutput)->s_arg, (*aoutput)->width - offset_width);
}

void	width_padding(t_arg **ainfo, t_data **aoutput)
{
	char	pad_ch;
	pad_ch = get_pad_ch(ainfo, aoutput);
	if (is_left_just(ainfo) || ((*ainfo)->spec == 'p' && is_zero_flag(ainfo)))
		handle_left_just(ainfo, aoutput, pad_ch);
	else
		handle_right_just(ainfo, aoutput, pad_ch);
}

void	handle_left_just(t_arg **ainfo, t_data **aoutput, char c)
{
	// pad len
	int	i;
	// safeguard for pad len (offset i)
	int	j;
	// padding 0s if precision > len
	int	k;

	// below condition applies only to when spec is 's' || 'd' || 'i' (line 165)
	if ((*ainfo)->precis != -1 && (*ainfo)->precis != 0 && (*ainfo)->precis < (*aoutput)->len &&
		((*ainfo)->spec == 's' || (*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
		i = (*ainfo)->precis;
	// below condition applies only to spec is (!is_hash_flag && ('o' || 'u')) || 'x' || 'X'
	else if ((*ainfo)->precis == 0 && (*ainfo)->precis < (*aoutput)->len &&
		ft_strcmp((*aoutput)->s_arg, "0") == 0 && (((!is_hash_flag(ainfo) &&
		((*ainfo)->spec == 'o' || (*ainfo)->spec == 'u' || (*ainfo)->spec == 'U')))
		|| (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
		i = 0;
	else	
		i = (*aoutput)->len;
	// special case when flag is present, but only if precision <= 1 AND hash flag is present
	// (i.e.), printf("%-#3.1o", 1);
	j = handle_left_prefix(ainfo, aoutput);
	// if precision > len, pad with '0's
	k = handle_left_precis(ainfo, aoutput, c);
	ft_memcpy((*aoutput)->presult, (*aoutput)->s_arg, i);
	// if k, pad the remaining with whitespaces
	if (k)
		ft_memset((*aoutput)->presult + i, ' ', (*aoutput)->width - i - j - k);
	else
		ft_memset(((*aoutput)->presult) + i, c, (*aoutput)->width - i - j);
}

int	handle_left_precis(t_arg **ainfo, t_data **aoutput, char c)
{
	int	precis;

	precis = 0;
	if ((*ainfo)->precis > (*aoutput)->len &&
		((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i' ||(*ainfo)->spec == 'o'
		 || (*ainfo)->spec == 'O' || (*ainfo)->spec == 'u' || (*ainfo)->spec == 'U'
		 || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X' || (*ainfo)->spec == 'D'))
	{
		precis = (*ainfo)->precis - (*aoutput)->len;
		ft_memset((*aoutput)->presult, c, precis);
		(*aoutput)->presult += precis;
	}
	return (precis);
}

// returns the offset, length of the prefix
int	handle_left_prefix(t_arg **ainfo, t_data **aoutput)
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

void	handle_right_just(t_arg **ainfo, t_data **aoutput, char c)
{
	// pad len
	int	i;
	int	j;

	j = 0;
	// special case when flag '#' is present and spec == 'x' || 'X'
	if ((*ainfo)->spec == 'p' || ((is_hash_flag(ainfo)
		&& ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X') && is_valid_x_width(ainfo, aoutput))))
		i = (*aoutput)->width - (*aoutput)->len - 2;
	// info->width must be > info->precision to pad right justify with ' '...
	else if ((*ainfo)->precis != -1 && (*ainfo)->width != -1 && (*ainfo)->width > (*ainfo)->precis)
	{
		i = (*aoutput)->width - (*ainfo)->precis;
		if ((*ainfo)->precis > (*aoutput)->len)
			handle_right_hlpr0(ainfo, aoutput, &i);
		// enters width padding -> handle right just, need to offset the 'pad' len of i...
		// refactor??? hacky condition for spec == 'o' || spec == 'u' || 'x' || 'X' 
		else if ((*ainfo)->precis < (*aoutput)->len && ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i' ||
			(*ainfo)->spec == 'o' || (*ainfo)->spec == 'O' || (*ainfo)->spec == 'u' ||
			(*ainfo)->spec == 'U' || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
			handle_right_hlpr1(ainfo, aoutput, &i);
		else if ((*aoutput)->len > (*ainfo)->precis && (*ainfo)->spec != 's')
			i = (*aoutput)->width - (*aoutput)->len;
	}
	else
		i = (*aoutput)->width - (*aoutput)->len;
	// checking if flag '+' exists while accounting for width padding
	handle_right_pads(ainfo, aoutput, c, &i);
	if (*(*aoutput)->s_arg == '-' && c == '0' && ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
		j = 1;
	//ft_memcpy(((*aoutput)->presult) + i, (*aoutput)->s_arg + j, (*aoutput)->width - i - j);
	ft_memcpy(((*aoutput)->presult) + i, (*aoutput)->s_arg + j, (*aoutput)->width - ((*aoutput)->presult - (*aoutput)->result) - i);
}

void	handle_right_hlpr1(t_arg **ainfo, t_data **aoutput, int *ai)
{
	if ((*ainfo)->precis == 0 && ft_strcmp((*aoutput)->s_arg, "0") == 0 &&
		(!is_hash_flag(ainfo) || (is_hash_flag(ainfo) && ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))))
		*ai = (*aoutput)->width;
	// below condition else if ((*aoutput)->width > (*aoutput)->len)
	else
		*ai = (*aoutput)->width - (*aoutput)->len;

}

int	is_valid_x_width(t_arg **ainfo, t_data **aoutput)
{
	int	tmp;

	tmp = 0;
	if ((*ainfo)->width == (*aoutput)->width && (*ainfo)->precis > (*aoutput)->len)
	{
		tmp = (*ainfo)->width - (*ainfo)->precis - 2;
		if (tmp > 0)
			return (0);
	}
	return (1);
}

void	handle_right_hlpr0(t_arg **ainfo, t_data **aoutput, int *ai)
{
	int	j;

	j = 0;
	// '+' flag && width > precision && width > s_len
	// ' ' flag is present, need to offset by 1 (width - precision)
	if ((is_plus_flag(ainfo) && is_valid_width(ainfo, aoutput)) || is_space_flag(ainfo))
		j = 1;
	// '#' flag is present
	else if (is_hash_flag(ainfo) && ft_strcmp((*aoutput)->s_arg, "0") != 0 &&
		((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X'))
		j = 2;
	else if (((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i') && *(*aoutput)->s_arg == '-')
		j = 1;
	ft_memset(((*aoutput)->presult), ' ', *ai - j);
	(*aoutput)->presult += (*ai - j);
	if (j == 2)
		*ai = (*ainfo)->precis - (*aoutput)->len;
	else
		*ai = (*ainfo)->precis - (*aoutput)->len + j;
}

int	is_valid_width(t_arg **ainfo, t_data **aoutput)
{
	if ((*aoutput)->width > (*ainfo)->precis && (*ainfo)->precis != -1 && (*aoutput)->width > (*aoutput)->len)
		return (1);
	return (0);
}

// handles width padding + precision padding + prefix
void	handle_right_pads(t_arg **ainfo, t_data **aoutput, char c, int *ai)
{
	(*aoutput)->flag = find_flag(ainfo, aoutput);
	if ((*aoutput)->flag)
	{
		if (*ai > 1 && (*aoutput)->flag != 'x' && (*aoutput)->flag != 'X')
			handle_right_pads0(aoutput, c, ai);
		else if ((*aoutput)->flag == 'x' || (*aoutput)->flag == 'X')
			handle_right_pads1(aoutput, c, ai);
		else
			*(*aoutput)->presult = (*aoutput)->flag;
	}
	else
	{
		// weird case when s_arg is negative, the '-' goes before the padding
		if (*(*aoutput)->s_arg == '-' && c == '0' && ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
			*(*aoutput)->presult++ = '-';
		ft_memset((*aoutput)->presult, c, *ai);
	}
}

void	handle_right_pads0(t_data **aoutput, char c, int *ai)
{
	(*ai)--;
	if (c == ' ')
	{
		ft_memset((*aoutput)->presult, c, *ai);
		*((*aoutput)->presult++ + *ai) = (*aoutput)->flag;
	}
	else
	{
		*(*aoutput)->presult++ = (*aoutput)->flag;
		ft_memset((*aoutput)->presult, c, *ai);
	}
}

void	handle_right_pads1(t_data **aoutput, char c, int *ai)
{
	if (*ai)
	{
		if (c == ' ')
		{
			ft_memset((*aoutput)->presult, c, *ai);
			*((*aoutput)->presult + *ai) = '0';
			*((*aoutput)->presult + *ai + 1) = (*aoutput)->flag;
		}
		else
		{
			*((*aoutput)->presult) = '0';
			*((*aoutput)->presult + 1) = (*aoutput)->flag;
			ft_memset((*aoutput)->presult + 2, c, *ai);
		}
	}
	else
	{
		*((*aoutput)->presult) = '0';
		*((*aoutput)->presult + 1) = (*aoutput)->flag;
	}
	(*ai) += 2;
}

char	find_flag(t_arg **ainfo, t_data **aoutput)
{
	if (is_plus_flag(ainfo) && *(*aoutput)->s_arg != '-')
		return ('+');
	else if (is_space_flag(ainfo))
		return (' ');
	// MUST be s_arg != "0" to avoid double `00`
	// swapped line 354 with 343 due to hierarchy...
	else if ((is_hash_flag(ainfo) || (*ainfo)->spec == 'p'))
	{
		if ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'p')
			return ('x');
		else if ((*ainfo)->spec == 'X')
			return ('X');
		return ('0');
	}
	// precision MUST be > (*aoutput)->len
	// left-pads the number with zeros instead of spaces, where padding is specified by width
	// fix the (*ainfo)->width > 0, may cause bugs
	else if (is_zero_flag(ainfo) && (*ainfo)->precis > (*aoutput)->len)
		return ('0');
	return (0);
}

char	get_pad_ch(t_arg **ainfo, t_data **aoutput)
{
	// took out (*ainfo)->spec != 's'
	if (((is_zero_flag(ainfo) && !is_left_just(ainfo) && (((*ainfo)->precis == -1 && (*ainfo)->width > (*aoutput)->len) || ((*ainfo)->precis == 0 && (*ainfo)->spec != 'd' && (*ainfo)->spec != 'i')))  		|| ((*ainfo)->spec != 's' && (*ainfo)->precis > (*aoutput)->len)
		|| ((*ainfo)->spec != 's' && ((*ainfo)->precis >= (*aoutput)->width
		|| (*ainfo)->precis > (*aoutput)->len))
		|| ((*ainfo)->precis == (*aoutput)->len && *(*aoutput)->s_arg == '-')))
		return ('0');
	else if ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O' || (*ainfo)->spec == 'u' || (*ainfo)->spec == 'U'
		|| (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X' || (*ainfo)->spec == 'D')
	{
		if ((*ainfo)->precis >= (*aoutput)->width || (*ainfo)->precis > (*aoutput)->len)
			return ('0');
		// 4-18-17 -> added -> !is_left_just(ainfo)
		else if ((*ainfo)->precis == -1 && (*aoutput)->width > (*aoutput)->len && is_zero_flag(ainfo) && !is_left_just(ainfo))
			return ('0');
	}
	return (' ');
}

//int	is_valid_precis_pad(t_arg **ainfo, t_data **aoutput)
//{
//	int	tmp;
//
//	if ((tmp = (*ainfo)->precis - ((*aoutput)->len - 1)) > 1)
//	
//}

void	update_result(t_arg **ainfo, t_data **aoutput)
{
	(*aoutput)->result = ft_strnew((*aoutput)->width += increment_width(ainfo, aoutput));
	(*aoutput)->presult = (*aoutput)->result;
}

int	increment_width(t_arg **ainfo, t_data **aoutput)
{
	int	cnt;

	cnt = 0;
	// took out !is_valid_width(ainfo, aoutput) &&
	if (is_plus_flag(ainfo) && !is_valid_width(ainfo, aoutput) && *(*aoutput)->s_arg != '-' && (*ainfo)->spec != 'p' &&
		((*aoutput)->len >= (*aoutput)->width || (*ainfo)->precis > (*aoutput)->len))
		cnt++;
	// 4-18-17 -> added (*ainfo)->spec != '%'
	// if flag ' ' is present and has enough width to insert the flag ' '
	if (is_space_flag(ainfo) && is_valid_space_flag(ainfo, aoutput) &&
		((*aoutput)->width <= (*ainfo)->precis || (*aoutput)->width <= (*aoutput)->len))
		cnt++;
	// if flag '#' is present and (*aoutput)->s_arg != "0" and len >= width
	// if flag '#' && spec 'x' || 'X' && (*aoutput)->s_arg != "0", increment width by 2 
	if (is_hash_flag(ainfo) && ft_strcmp((*aoutput)->s_arg, "0") != 0)
	{
		if ((*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')
			cnt += incr_width_hlpr(ainfo, aoutput);
		else if ((*aoutput)->len >= (*aoutput)->width && ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O'))
			cnt++;
	}
	if (((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i') &&
		(*ainfo)->precis > (*aoutput)->len && (*ainfo)->precis >= (*aoutput)->width && *(*aoutput)->s_arg == '-')
		cnt++;
	if ((*ainfo)->spec == 'p')
		cnt += incr_width_hlpr(ainfo, aoutput);
	return (cnt);
}

int	is_valid_space_flag(t_arg **ainfo, t_data **aoutput)
{
	if (((((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i') && (*(*aoutput)->s_arg == '-' || is_plus_flag(ainfo))) ||
	(*ainfo)->spec == 'u' || (*ainfo)->spec == 'U' || (*ainfo)->spec == 'c' || (*ainfo)->spec == 'o' || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X' || (*ainfo)->spec == '%' || (*ainfo)->spec == 's' || (*ainfo)->spec == 'C' || (*ainfo)->spec == 'S') || (*ainfo)->spec == 'p')
		return (0);
	return (1);
}

// returns the additional width required for spec == 'x' || 'X' when the flag '#' is present
int	incr_width_hlpr(t_arg **ainfo, t_data **aoutput)
{
	int	tmp;
	// a bug may occur.... here
	tmp = 0;
	if ((*aoutput)->width == 1 ||
		((*ainfo)->precis > (*aoutput)->len && (*ainfo)->precis >= (*aoutput)->width) ||
		 ((*aoutput)->len >= (*ainfo)->width && (*aoutput)->len >= (*ainfo)->precis))
		return (2);
	else if ((*aoutput)->width == 2)
		return (1);
	else if ((*ainfo)->width > (*aoutput)->len && (*aoutput)->len > (*ainfo)->precis)
		tmp = (*aoutput)->width - (*aoutput)->len;
	else if ((*aoutput)->width > (*ainfo)->precis && (*ainfo)->precis > (*aoutput)->len)
		tmp = (*aoutput)->width - (*ainfo)->precis;
	return (tmp <= 1 ? tmp : 0);
}

int	is_hash_flag(t_arg **ainfo)
{
	return ((*ainfo)->flags[HASH_IDX] ? 1 : 0);
}

int	is_space_flag(t_arg **ainfo)
{
	return ((*ainfo)->flags[SPACE_IDX] ? 1 : 0);
}

int	is_zero_flag(t_arg **ainfo)
{
	return ((*ainfo)->flags[ZERO_IDX] ? 1 : 0);
}

// checks if '+' flag is present for specifier 'd' and 'i'
int	is_plus_flag(t_arg **ainfo)
{
	if ((*ainfo)->flags[PLUS_IDX] && ((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i' || (*ainfo)->spec == 'D' || (*ainfo)->spec == 'p'))
		return (1);
	return (0);
}

void	get_precision(t_arg **ainfo, t_data **aoutput)
{
	if ((*ainfo)->precis != -1)
	{
		if ((*ainfo)->spec == 's')
		{
			if ((*ainfo)->width > (*ainfo)->precis)
				(*aoutput)->width = (*ainfo)->width;
			else if ((*ainfo)->precis >= (*ainfo)->width && (*ainfo)->precis <= (*aoutput)->len)
				(*aoutput)->width = (*ainfo)->precis;
			else if ((*ainfo)->precis > (*aoutput)->width && (*aoutput)->width < (*aoutput)->len) 
				(*aoutput)->width = (*aoutput)->len;
		}
		else if (((*ainfo)->spec == 'd' || (*ainfo)->spec == 'i'))
		{
			// refactor?
			if ((*ainfo)->precis == 0 && ft_strcmp((*aoutput)->s_arg, "0") == 0)
			{
				if ((*ainfo)->width == -1)
					(*aoutput)->width = 0;
			}
			//else if ((*ainfo)->precis <= (*aoutput)->len)
			//	(*ainfo)->precis = (*aoutput)->len;
			else if ((*ainfo)->precis > (*aoutput)->width)
				(*aoutput)->width = (*ainfo)->precis;
			//if (*(*aoutput)->s_arg == '-' && (*ainfo)->precis > (*aoutput)->len)
			//	(*aoutput)->width++;
		}
		else if ((*ainfo)->spec == 'o' || (*ainfo)->spec == 'O' || (*ainfo)->spec == 'u' || (*ainfo)->spec == 'U'
			|| (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X' || (*ainfo)->spec == 'D' || (*ainfo)->spec == 'p')
		{
			// if spec == 'o' AND precision && s_arg == 0 and width <= 0 --> no chars are printed unless a '#' flag is present
			// if spec == 'x' || 'X', precision AND s_arg == 0, width <= 0, '#' flag is present, set width to 0
			if ((*ainfo)->precis == 0 && ft_strcmp((*aoutput)->s_arg, "0") == 0 && (*ainfo)->width <= 0)
			{
				if (!is_hash_flag(ainfo) || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X' || (*ainfo)->spec == 'p')
					(*aoutput)->width = 0;
			}
			else if ((*ainfo)->precis > (*aoutput)->width)
				(*aoutput)->width = (*ainfo)->precis;
		}
	}
	//else if ((*ainfo)->precis == -1 && ft_strcmp((*aoutput)->s_arg, "0") == 0)
	//	(*ainfo)->precis = 0;
}

void	get_min_width(t_arg **ainfo, t_data **aoutput)
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

int	is_left_just(t_arg **ainfo)
{
	return ((*ainfo)->flags[MINUS_IDX] ? 1 : 0);
}

int	is_width_pad(t_arg **ainfo, int s_len)
{
	if ((((*ainfo)->width > (*ainfo)->precis && (*ainfo)->precis != -1 &&
		(!is_hash_flag(ainfo) || (*ainfo)->spec == 'x' || (*ainfo)->spec == 'X')) 
		|| (((*ainfo)->width > s_len) && (*ainfo)->width != -1))
		|| (*ainfo)->precis > s_len)
		return (1);
	return (0);
}

void	populate_info(char **aformat_cpy, t_arg **ainfo, va_list ap)
{
	populate_flags(aformat_cpy, ainfo);
	populate_width(aformat_cpy, ainfo, ap);
	populate_precision(aformat_cpy, ainfo, ap);
	populate_length(aformat_cpy, ainfo);
	populate_specifier(aformat_cpy, ainfo);
}

void	populate_length(char **aformat_cpy, t_arg **ainfo)
{
	int	tmp;

	while (**aformat_cpy)
	{
		if (is_length(**aformat_cpy))
		{
			tmp = get_length(aformat_cpy);
			if (tmp > (*ainfo)->leng)
				(*ainfo)->leng = tmp;
			if (tmp == hh || tmp == ll)
				(*aformat_cpy)++;
			(*aformat_cpy)++;
		}
		else
			break ;
	}
}

int	get_length(char **aformat_cpy)
{
	if (**aformat_cpy == 'h' && *(*aformat_cpy + 1) == 'h')
		return (hh);
	else if (**aformat_cpy == 'l' && *(*aformat_cpy + 1) == 'l')
		return (ll);
	else if (**aformat_cpy == 'h')
		return (h);
	else if (**aformat_cpy == 'l')
		return (l);
	else if (**aformat_cpy == 'j')
		return (j);
	else if (**aformat_cpy == 'z')
		return (z);
	return (0);
}

int	is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

void	populate_flags(char **aformat_cpy, t_arg **ainfo)
{
	while (**aformat_cpy)
	{
		if (is_flag(**aformat_cpy))
			(*ainfo)->flags[get_idx_flag(**aformat_cpy)] = '1';
		else
			break ;
		(*aformat_cpy)++;
	}
}

void	populate_width(char **aformat_cpy, t_arg **ainfo, va_list ap)
{
	// took out ft_isdigit || **aformat_cpy == '*' on line 809
	while (**aformat_cpy)
	{
		if (ft_isdigit(**aformat_cpy))
			(*ainfo)->width = get_num(aformat_cpy);
		else if (**aformat_cpy == '*')
		{
			if (((*ainfo)->width = va_arg(ap, int)) < 0)
			{
				(*ainfo)->flags[MINUS_IDX] = 1;
				(*ainfo)->width *= -1;
			}
			(*aformat_cpy)++;
		}
		else
			break ;
	}
}

void	populate_precision(char **aformat_cpy, t_arg **ainfo, va_list ap)
{
	while (**aformat_cpy)
	{
		if (**aformat_cpy == '.')
		{
			(*aformat_cpy)++;
			if (ft_isdigit(**aformat_cpy))
				(*ainfo)->precis = get_num(aformat_cpy);
			else if (**aformat_cpy == '*')
			{
				if (((*ainfo)->precis = va_arg(ap, int)) < 0)
					(*ainfo)->precis = -1;
				(*aformat_cpy)++;
			}
			else
				(*ainfo)->precis = 0;
		}
		else
			break ;
	}
}

void	populate_specifier(char **aformat_cpy, t_arg **ainfo)
{
	while (**aformat_cpy)
	{
		if (is_specifier(**aformat_cpy))
		{
			(*ainfo)->spec = **aformat_cpy;
			break ;
		}
		else
		{
			if (is_flag(**aformat_cpy))
			{
				(*ainfo)->flags[get_idx_flag(**aformat_cpy)] = '1';
				(*aformat_cpy)++;
			}
			else
				break ;
		}
	}
}

int	is_specifier(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
	    c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
	    c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

int	get_num(char **aformat_cpy)
{
	int	res;

	res = 0;
	while (ft_isdigit(**aformat_cpy))
	{
		res = (res * 10) + ((**aformat_cpy) - '0');
		(*aformat_cpy)++;
	}
	return (res);
}

int	get_idx_flag(char c)
{
	if (c == '-')
		return (MINUS_IDX);
	else if (c == '+')
		return (PLUS_IDX);
	else if (c == ' ')
		return (SPACE_IDX);
	else if (c == '0')
		return (ZERO_IDX);
	else
		return (HASH_IDX);
}

int	is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '0' || c == '#')
		return (1);
	return (0);
}

void	init_output(t_data **aoutput)
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

void	init_info(t_arg **ainfo)
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

int	get_base(char spec)
{
	if (spec == 'o' || spec == 'O')
		return (8);
	else if (spec == 'x' || spec == 'X' || spec == 'p')
		return (16);
	return (10);
}

int	uintmax_numlen(uintmax_t n, int b)
{
	int	len;

	len = 0;
	while (n) 
	{
		len++;
		n /= b;
	}
	return (len);
}

int	intmax_numlen(intmax_t n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*intmax_to_a(intmax_t value)
{
	int	isneg;
	int	len;
	char	*s;
	char	*ps;

	isneg = 0;
	if (value == 0)
	{
		if (!(s = ft_strnew(2)))
			return (NULL);
		*s = '0';
		return (s);
	}
	else if (value < 0)
		isneg = 1;
	len = intmax_numlen(value);
	if (!(s = ft_strnew(len + isneg)))
		return (NULL);
	ps = s;
	if (isneg)
		*ps++ = '-';
	while (value)
	{
		if (isneg)
			*ps++ = ((value % 10) * -1) + 48;
		else
			*ps++ = (value % 10) + 48;
		value /= 10;
	}
	return (ft_strrev(s));
}
char	*uintmax_to_a_base(uintmax_t value, int base, char spec)
{
	int	len;
	char	*s;
	char	*ps;
	char	*b;

	b = (spec == 'X' ? "0123456789ABCDEF" : "0123456789abcdef");
	if (value == 0)
	{
		if (!(s = ft_strnew(1)))
			return (NULL);
		*s = '0';
		return (s);
	}
	len = uintmax_numlen(value, base);
	if (!(s = ft_strnew(len)))
		return (NULL);
	ps = s;
	while (value)
	{
		*ps++ = b[(value % base)];
		value /= base;
	}
	return (ft_strrev(s));
}
