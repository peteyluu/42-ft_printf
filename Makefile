# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pluu <pluu@student.42.us.org>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/07 15:50:50 by pluu              #+#    #+#              #
#    Updated: 2017/05/07 15:51:09 by pluu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CC	= gcc

FLAGS	= -Wall -Wextra -Werror

SRCS    =  srcs/ft_printf.c \
	   srcs/init_structs.c \
	   srcs/bool_flags.c \
	   srcs/bool_hlprs.c \
	   srcs/format_parser.c \
	   srcs/get_flags.c \
	   srcs/get_width_precis.c \
	   srcs/get_leng.c \
	   srcs/get_spec.c \
	   srcs/handle_va_arg.c \
	   srcs/handle_va_arg1.c \
	   srcs/handle_va_arg2.c \
	   srcs/handle_wchars.c \
	   srcs/handle_wchar.c \
	   srcs/uintmax_to_a_base.c \
	   srcs/intmax_to_a.c \
	   srcs/unicode_to_utf8.c \
	   srcs/handle_output.c \
	   srcs/get_min_width.c \
	   srcs/prep_output.c \
	   srcs/handle_padding.c \
	   srcs/handle_left_just.c \
	   srcs/handle_right_just.c \
	   srcs/handle_right_pads.c \
	   srcs/libft/ft_memset.c \
	   srcs/libft/ft_bzero.c \
	   srcs/libft/ft_memcpy.c \
	   srcs/libft/ft_memccpy.c \
	   srcs/libft/ft_memmove.c \
	   srcs/libft/ft_memchr.c \
	   srcs/libft/ft_memcmp.c \
	   srcs/libft/ft_strlen.c \
	   srcs/libft/ft_strdup.c \
	   srcs/libft/ft_strcpy.c \
	   srcs/libft/ft_strncpy.c \
	   srcs/libft/ft_strcat.c \
	   srcs/libft/ft_strncat.c \
	   srcs/libft/ft_strlcat.c \
	   srcs/libft/ft_strchr.c \
	   srcs/libft/ft_strrchr.c \
	   srcs/libft/ft_strstr.c \
	   srcs/libft/ft_strnstr.c \
	   srcs/libft/ft_strcmp.c \
	   srcs/libft/ft_strncmp.c \
	   srcs/libft/ft_atoi.c \
	   srcs/libft/ft_isalpha.c \
	   srcs/libft/ft_isdigit.c \
	   srcs/libft/ft_isalnum.c \
	   srcs/libft/ft_isascii.c \
	   srcs/libft/ft_isprint.c \
	   srcs/libft/ft_toupper.c \
	   srcs/libft/ft_tolower.c \
	   srcs/libft/ft_memalloc.c \
	   srcs/libft/ft_memdel.c \
	   srcs/libft/ft_strnew.c \
	   srcs/libft/ft_strdel.c \
	   srcs/libft/ft_strclr.c \
	   srcs/libft/ft_striter.c \
	   srcs/libft/ft_striteri.c \
	   srcs/libft/ft_strmap.c \
	   srcs/libft/ft_strmapi.c \
	   srcs/libft/ft_strequ.c \
	   srcs/libft/ft_strnequ.c \
	   srcs/libft/ft_strsub.c \
	   srcs/libft/ft_strjoin.c \
	   srcs/libft/ft_strtrim.c \
	   srcs/libft/ft_strsplit.c \
	   srcs/libft/ft_itoa.c \
	   srcs/libft/ft_putchar.c \
	   srcs/libft/ft_putstr.c \
	   srcs/libft/ft_putendl.c \
	   srcs/libft/ft_putnbr.c \
	   srcs/libft/ft_putchar_fd.c \
	   srcs/libft/ft_putstr_fd.c \
	   srcs/libft/ft_putendl_fd.c \
	   srcs/libft/ft_putnbr_fd.c \
	   srcs/libft/ft_lstnew.c \
	   srcs/libft/ft_lstdelone.c \
	   srcs/libft/ft_lstdel.c \
	   srcs/libft/ft_lstadd.c \
	   srcs/libft/ft_lstiter.c \
	   srcs/libft/ft_lstmap.c \
	   srcs/libft/ft_wordcnt.c \
	   srcs/libft/ft_strrev.c \
	   srcs/libft/ft_lstpush.c \
	   srcs/libft/ft_issort.c \
	   srcs/libft/ft_isprime.c

O       = $(SRCS:.c=.o)

OBJS	= $(addprefix ./objs/, $(notdir $(O)))
INC	= -I./incs/ft_printf.h

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRCS) $(INC) -g
	mkdir objs
	mv *.o objs
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -rf objs

fclean: clean
	rm -rf $(NAME)

re: fclean all
