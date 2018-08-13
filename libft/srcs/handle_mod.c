/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:38 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_mod(char **format, va_list args, int *count)
{
	char	*ptr;
	t_data	*info;

	ptr = ++(*format);
	info = init_data();
	parse_flags(info, &ptr);
	parse_width(info, &ptr);
	parse_precision(info, &ptr);
	parse_length(info, &ptr);
	parse_specifier(info, &ptr);
	print_format(info, args, count);
	*format = ptr;
	free(info->length);
	free(info);
}
