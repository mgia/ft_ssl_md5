/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:38 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_str(char *str, int *count)
{
	ft_putstr(str);
	*count += ft_strlen(str);
	free(str);
}

void		print_format(t_data *info, va_list args, int *count)
{
	char	*str;

	if (info->specifier == 'S' || (info->specifier == 's'
		&& ft_strequ(info->length, "l")))
		str = format_big_s(info, args);
	else if (info->specifier == 's')
		str = format_s(info, args);
	else if (info->specifier == 'p')
		str = format_p(args);
	else if (info->specifier == 'd' || info->specifier == 'D' ||
			info->specifier == 'i')
		str = format_d(info, args);
	else if (info->specifier == 'o' || info->specifier == 'O')
		str = format_o(info, args);
	else if (info->specifier == 'u' || info->specifier == 'U')
		str = format_u(info, args);
	else if (info->specifier == 'x' || info->specifier == 'X')
		str = format_x(info, args);
	else if (info->specifier == 'c' || info->specifier == 'C')
		str = format_c(info, args, count);
	else if (info->specifier == '%')
		str = format_mod(info);
	else
		return ;
	print_str(str, count);
}
