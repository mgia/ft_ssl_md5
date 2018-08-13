/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:38 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_flags(t_data *info, char **format)
{
	if (**format == '#')
		info->hex = 1;
	else if (**format == '-')
		info->minus = 1;
	else if (**format == '+')
		info->plus = 1;
	else if (**format == ' ')
		info->space = 1;
	else if (**format == '0')
		info->zero = 1;
	else
		return (0);
	return (1);
}

int			check_length(char **ref, char *str)
{
	while (*ref)
	{
		if (ft_strstr(*ref, str))
			return (1);
		ref++;
	}
	return (0);
}

int			check_specifier(char c)
{
	static char	*list = "sSpdDioOuUxXcC%";
	int			i;

	i = -1;
	while (list[++i])
		if (list[i] == c)
			return (1);
	return (0);
}

intmax_t	get_signed(t_data *info, va_list args)
{
	intmax_t	num;

	if (info->specifier == 'D' || ft_strequ(info->length, "l"))
		num = va_arg(args, long);
	else if (ft_strequ(info->length, "ll"))
		num = va_arg(args, long long);
	else if (ft_strequ(info->length, "ll"))
		num = va_arg(args, long long);
	else if (ft_strequ(info->length, "h"))
		num = (short int)va_arg(args, int);
	else if (ft_strequ(info->length, "hh"))
		num = (char)va_arg(args, int);
	else if (ft_strequ(info->length, "z"))
		num = va_arg(args, size_t);
	else if (ft_strequ(info->length, "j"))
		num = va_arg(args, intmax_t);
	else
		num = va_arg(args, int);
	return (num);
}

uintmax_t	get_unsigned(t_data *info, va_list args)
{
	uintmax_t	num;

	if (info->specifier == 'O' || info->specifier == 'U' ||
		ft_strequ(info->length, "l"))
		num = va_arg(args, unsigned long);
	else if (ft_strequ(info->length, "ll"))
		num = va_arg(args, unsigned long long);
	else if (ft_strequ(info->length, "h"))
		num = va_arg(args, unsigned int) & 0xFFFF;
	else if (ft_strequ(info->length, "hh"))
		num = va_arg(args, unsigned int) & 0xFF;
	else if (ft_strequ(info->length, "z"))
		num = va_arg(args, size_t);
	else if (ft_strequ(info->length, "j"))
		num = va_arg(args, uintmax_t);
	else
		num = va_arg(args, unsigned int);
	return (num);
}
