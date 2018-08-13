/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:38 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_data		*init_data(void)
{
	t_data *info;

	info = malloc(sizeof(t_data));
	info->hex = 0;
	info->zero = 0;
	info->minus = 0;
	info->plus = 0;
	info->space = 0;
	info->width = 0;
	info->dot = 0;
	info->precision = 0;
	info->length = "";
	info->specifier = '\0';
	return (info);
}

static void	init_types(char **modifier)
{
	modifier[0] = "hh";
	modifier[1] = "h";
	modifier[2] = "l";
	modifier[3] = "ll";
	modifier[4] = "j";
	modifier[5] = "z";
}

char		**init_length_specifiers(void)
{
	char	**tmp;

	tmp = malloc(sizeof(char**) * (6 + 1));
	tmp[6] = 0;
	init_types(tmp);
	return (tmp);
}
