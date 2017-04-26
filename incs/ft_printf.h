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
# define SENTINEL -2

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

int	ft_printf(const char *format, ...);
void	ft_putstr_nbytes(char *s, size_t n);
void	populate_info(char **aformat_cpy, t_arg **ainfo, va_list ap);
void	populate_flags(char **aformat_cpy, t_arg **ainfo);
void	populate_width(char **aformat_cpy, t_arg **ainfo, va_list ap);
void	populate_precision(char **aformat_cpy, t_arg **ainfo, va_list ap);
void	populate_length(char **aformat_cpy, t_arg **ainfo);
int	is_length(char c);
int	get_length(char **aformat_cpy);
void	populate_specifier(char **aformat_cpy, t_arg **ainfo);
int	populate_result(t_arg **ainfo, t_data **aoutput);
void	pop_res_hlpr(t_arg **ainfo, t_data **aoutput);
int	is_flag(char c);
int	get_idx_flag(char c);
int	get_num(char **aformat_cpy);
int	is_specifier(char c);
void	get_min_width(t_arg **ainfo, t_data **output);
void	get_precision(t_arg **ainfo, t_data **aoutput);
void	update_result(t_arg **ainfo, t_data **aoutput);
void	width_padding(t_arg **ainfo, t_data **aoutput);
int	is_width_pad(t_arg **ainfo, int s_len);
int	is_left_just(t_arg **ainfo);
void	handle_left_just(t_arg **ainfo, t_data **aoutput, char c);
//void	handle_left_hlpr(t_arg **ainfo, t_data **aoutput, char c, int *ak);
int	handle_left_prefix(t_arg **ainfo, t_data **aoutput);
int	handle_left_precis(t_arg **ainfo, t_data **aoutput, char c);
void	handle_right_just(t_arg **ainfo, t_data **aoutput, char c);
void	handle_right_hlpr0(t_arg **ainfo, t_data **aoutput, int *ai);
void	handle_right_hlpr1(t_arg **ainfo, t_data **aoutput, int *ai);
void	handle_right_pads(t_arg **ainfo, t_data **aoutput, char c, int *ai);
void	handle_right_pads0(t_data **aoutput, char c, int *ai);
void	handle_right_pads1(t_data **aoutput, char c, int *ai);
char	find_flag(t_arg **ainfo, t_data **aoutput);
void	handle_va_arg(t_arg **ainfo, t_data **aoutput, char **aformat_cpy, va_list ap);
char	get_pad_ch(t_arg **ainfo, t_data **aoutput);
void	init_info(t_arg **ainfo);
void	init_output(t_data **aoutput);
void	dispose_structs(t_arg **ainfo, t_data **aoutput);
//void	dispose_structs(t_arg **ainfo);
// increment width by 1, for flags '+' || ' '
int	increment_width(t_arg **ainfo, t_data **aoutput);
int	incr_width_hlpr(t_arg **ainfo, t_data **aoutput);
int	is_valid_space_flag(t_arg **ainfo, t_data **aoutput);
int	is_plus_flag(t_arg **ainfo);
int	is_valid_width(t_arg **ainfo, t_data **aoutput);
int	is_space_flag(t_arg **ainfo);
int	is_zero_flag(t_arg **ainfo);
int	is_hash_flag(t_arg **ainfo);
/* modified ft_itoa_base */
int	get_base(char spec);
int	uintmax_numlen(uintmax_t n, int b);
char	*uintmax_to_a_base(uintmax_t value, int base, char spec);
int	intmax_numlen(intmax_t n);
char	*intmax_to_a(intmax_t value);
// check if the width is valid for width padding when spec == 'x' || 'X'
// perhaps rename later?
int	is_valid_x_width(t_arg **ainfo, t_data **aoutput);
/* wide character strings */
char	*handle_wstr(wchar_t *ws, t_arg **ainfo);
int	get_byte_cnt(wchar_t wc);
void	unicode_to_utf8(wchar_t wc, char **as);
char	*handle_wch(wchar_t wc);
#endif
