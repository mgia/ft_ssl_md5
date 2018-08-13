/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:38 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*format_s(t_data *info, va_list args)
{
	char	*str;
	int		len;

	str = va_arg(args, char *);
	if (!str)
		return (ft_strdup("(null)"));
	else
		str = ft_strdup(str);
	len = ft_strlen(str);
	if (info->dot && info->precision < len)
		str = slice_right(&str, len - info->precision);
	if (info->minus)
		str = pad_right(&str, info->width, ' ');
	else
		str = pad_left(&str, info->width, ' ');
	return (str);
}

char	*format_big_s(t_data *info, va_list args)
{
	wchar_t		*str;
	char		*tmp;
	int			len;
	int			i;

	str = (wchar_t *)va_arg(args, void *);
	len = 0;
	i = 0;
	if (!str)
		return (ft_strdup("(null)"));
	while (str[len++])
		len++;
	tmp = malloc(len + 1);
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	if (info->dot && info->precision < len)
		tmp = slice_right(&tmp, len - info->precision);
	if (!info->minus)
		tmp = pad_left(&tmp, info->width, ' ');
	else
		tmp = pad_right(&tmp, info->width, ' ');
	return (tmp);
}

char	*format_p(va_list args)
{
	char *str;

	str = ft_itoa_base((unsigned long int)va_arg(args, char *), 16);
	str = ft_strjoin("0x", &str);
	return (str);
}
