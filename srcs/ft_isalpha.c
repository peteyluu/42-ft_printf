/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pluu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:32:18 by pluu              #+#    #+#             */
/*   Updated: 2017/01/12 16:38:16 by pluu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_isalpha(int c)
{
	return (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) ? 1 : 0);
}
