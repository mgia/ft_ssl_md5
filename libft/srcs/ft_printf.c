/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:38 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(char *format, ...)
{
	va_list	list;
	int		count;

	count = 0;
	va_start(list, format);
	while (*format)
	{
		if (*format == '%')
			handle_mod(&format, list, &count);
		else
		{
			ft_putchar(*format);
			format++;
			count++;
		}
	}
	va_end(list);
	return (count);
}
