/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:51:46 by pluu              #+#    #+#             */
/*   Updated: 2017/05/08 13:58:59 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../incs/libft.h"
# define NUM_FLAGS 5
# define NUM_LENGTH 2
# define MINUS_IDX 0
# define PLUS_IDX 1
# define SPACE_IDX 2
# define ZERO_IDX 3
# define HASH_IDX 4

enum
{
	none,
	hh,
	h,
	ll,
	l,
	j,
	z
};

typedef struct	s_arg
{
	char	*flags;
	int	width;
	int	precis;
	int	leng;
	char	spec;
}		t_arg;

typedef struct	s_data
{
	char	*s_arg;
	int	free_arg;
	int	len;
	char	flag;
	int	width;
	char	*result;
	char	*presult;
}		t_data;

typedef struct	s_misc
{
	int	ret;
	char	*fmt_str;
	va_list	ap;
}		t_misc;

int	ft_printf(const char *format, ...);
void	populate_info(t_arg **ainfo, t_misc **amisc);
void	populate_flags(t_misc **amisc, t_arg **ainfo);
void	populate_width(t_misc **amisc, t_arg **ainfo);
void	populate_precision(t_misc **amisc, t_arg **ainfo);
void	populate_length(t_misc **amisc, t_arg **ainfo);
void	populate_specifier(t_misc **amisc, t_arg **ainfo);
int	populate_result(t_arg **ainfo, t_data **aoutput);
int	get_idx_flag(char c);
void	get_min_width(t_arg **ainfo, t_data **aoutput);
void	get_precis(t_arg **ainfo, t_data **aoutput);
int	get_byte_cnt(wchar_t wc);
char	find_flag(t_arg **ainfo, t_data **aoutput);
void	update_result(t_arg **ainfo, t_data **aoutput);
void	width_padding(t_arg **ainfo, t_data **aoutput);
void	handle_left_just(t_arg **ainfo, t_data **aoutput, char c);
void	handle_right_just(t_arg **ainfo, t_data **aoutput, char c);
void	handle_right_pads(t_arg **ainfo, t_data **aoutput, char c, int *ai);
void	handle_va_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc);
void	handle_s_arg(t_data **aoutput, t_misc **amisc);
void	handle_di_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc);
void	handle_c_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc);
void	handle_bd_arg(t_data **aoutput, t_misc **amisc);
void	handle_bou_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc);
void	handle_ouxX_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc);
void	handle_p_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc);
void	handle_bs_arg(t_arg **ainfo, t_data **aoutput, t_misc **amisc);
void	handle_bc_arg(t_data **aoutput, t_misc **amisc);
void	handle_def_arg(t_data **aoutput, t_misc **amisc);
void	handle_n_arg(t_misc **amisc);
void	init_info(t_arg **ainfo);
void	init_output(t_data **aoutput);
void	init_misc(t_misc **amisc, const char *format);
int	is_flag(char c);
int	is_width_pad(t_arg **ainfo, int s_len);
int	is_valid_space_flag(t_arg **ainfo, t_data **aoutput);
int	is_left_just(t_arg **ainfo);
int	is_plus_flag(t_arg **ainfo);
int	is_space_flag(t_arg **ainfo);
int	is_zero_flag(t_arg **ainfo);
int	is_hash_flag(t_arg **ainfo);
int	is_valid_width(t_arg **ainfo, t_data **aoutput);
char	*uintmax_to_a_base(uintmax_t value, int base, char spec);
char	*intmax_to_a(intmax_t value);
void	unicode_to_utf8(wchar_t wc, char **as);

#endif
