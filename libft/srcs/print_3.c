/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:38 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_strupper(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		*str = ft_toupper(*str);
		str++;
	}
}

char	*format_x(t_data *info, va_list args)
{
	uintmax_t	num;
	char		*str;
	int			p;

	num = get_unsigned(info, args);
	str = ft_itoa_base(num, 16);
	p = 0;
	if (info->dot && !info->precision && !num)
		str = ft_strdup("");
	else if (info->hex)
		p = 2;
	if (info->minus)
		str = pad_right(&str, info->width - p, ' ');
	else if (info->zero)
		str = pad_left(&str, info->width - p, '0');
	if (info->hex && num)
		str = ((info->specifier == 'x') ?
				ft_strjoin("0x", &str) :
				ft_strjoin("0X", &str));
	if (!(info->minus && info->zero))
		str = pad_left(&str, info->width, ' ');
	if (info->specifier == 'X')
		ft_strupper(str);
	return (str);
}

int		format_null(t_data *info, int *count)
{
	char		c;

	c = 0;
	if (!info->minus)
	{
		while (--info->width > 0 && ++(*count))
			ft_putchar(' ');
		write(1, &c, 1);
		(*count)++;
	}
	else if (info->minus)
	{
		write(1, &c, 1);
		(*count)++;
		while (--info->width > 0 && ++(*count))
			ft_putchar(' ');
	}
	return (1);
}

char	*format_c(t_data *info, va_list args, int *count)
{
	int		c;
	char	*str;

	str = ft_strnew(1);
	if (info->specifier == 'C' || ft_strequ(info->length, "l") ||
			ft_strequ(info->length, "ll"))
		c = va_arg(args, wchar_t);
	else
		c = (char)va_arg(args, void *);
	if (!c)
	{
		format_null(info, count);
		return (str);
	}
	str[0] = c;
	if (info->minus && info->width)
		str = pad_right(&str, info->width, ' ');
	else if (info->width)
		str = pad_left(&str, info->width, ' ');
	return (str);
}

char	*format_mod(t_data *info)
{
	char	*str;

	str = ft_strdup("%");
	if (info->minus)
		str = pad_right(&str, info->width, ' ');
	else if (info->zero)
		str = pad_left(&str, info->width, '0');
	else
		str = pad_left(&str, info->width, ' ');
	return (str);
}
