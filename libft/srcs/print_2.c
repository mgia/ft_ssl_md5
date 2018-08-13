/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:38 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*format_d(t_data *info, va_list args)
{
	intmax_t	num;
	char		*str;
	int			p;

	num = get_signed(info, args);
	p = (num < 0 || info->plus || info->space) ? 1 : 0;
	str = ft_itoa(num);
	str = (num < 0) ? slice_left(&str, 1) : str;
	str = (info->precision) ? pad_left(&str, info->precision, '0') : str;
	if (!info->minus && info->zero && !info->dot)
		str = pad_left(&str, info->width - p, '0');
	if (num < 0)
		str = ft_strjoin("-", &str);
	else if (info->plus)
		str = ft_strjoin("+", &str);
	else if (info->space)
		str = ft_strjoin(" ", &str);
	if (info->dot && !info->precision && !num)
		str = ft_strdup("");
	if (info->minus)
		str = pad_right(&str, info->width, ' ');
	else
		str = pad_left(&str, info->width, ' ');
	return (str);
}

static char	*format_u_2(t_data *info, char *str)
{
	int		len;

	len = ft_strlen(str);
	if (info->dot)
	{
		if (!info->precision)
		{
			if (ft_strequ(str, "0"))
				return (ft_strdup(""));
			str[0] = '\0';
		}
		else if (len < info->precision)
			str = pad_left(&str, info->precision, '0');
	}
	if (info->width)
	{
		if (info->minus)
			str = pad_right(&str, info->width, ' ');
		else if (info->zero)
			str = pad_left(&str, info->width, '0');
		else
			str = pad_left(&str, info->width, ' ');
	}
	return (str);
}

char		*format_u(t_data *info, va_list args)
{
	char		*str;

	str = ft_itoa_base(get_unsigned(info, args), 10);
	str = format_u_2(info, str);
	return (str);
}

char		*format_o(t_data *info, va_list args)
{
	uintmax_t	num;
	char		*str;
	int			p;

	num = get_unsigned(info, args);
	p = (info->hex) ? 1 : 0;
	str = ft_itoa_base(num, 8);
	if (info->dot && !info->precision && !num)
	{
		if (info->hex)
			str = ft_strdup("0");
		else
			str = ft_strdup("");
	}
	if (info->precision)
		str = pad_left(&str, info->precision - p, '0');
	if (!info->minus && info->zero)
		str = pad_left(&str, info->width, '0');
	if (info->hex && num)
		str = ft_strjoin("0", &str);
	if (info->minus)
		str = pad_right(&str, info->width, ' ');
	else
		str = pad_left(&str, info->width, ' ');
	return (str);
}
