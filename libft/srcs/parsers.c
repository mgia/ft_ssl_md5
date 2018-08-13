/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:38 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_printf_flags(t_data *info, char **format)
{
	while (check_flags(info, format))
		(*format)++;
}

void	parse_width(t_data *info, char **format)
{
	if (ft_isdigit(**format))
		info->width = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
}

void	parse_precision(t_data *info, char **format)
{
	char	*ptr;

	ptr = *format;
	if (*ptr != '.')
		return ;
	info->dot = 1;
	ptr++;
	*format = ptr;
	if (!ft_isdigit(*ptr))
		return ;
	info->precision = ft_atoi(ptr);
	while (ft_isdigit(*ptr))
		ptr++;
	*format = ptr;
}

void	parse_length(t_data *info, char **format)
{
	char	**ref;
	char	*tmp;
	int		i;

	if (!(*format))
		return ;
	i = 0;
	ref = init_length_specifiers();
	tmp = ft_strdup(*format);
	while (tmp[i] && !check_specifier(tmp[i]))
		i++;
	tmp[i] = '\0';
	if (check_length(ref, tmp))
	{
		info->length = ft_strdup(tmp);
		*format += i;
	}
	else
		info->length = ft_strdup("");
	free(ref);
	free(tmp);
}

void	parse_specifier(t_data *info, char **format)
{
	char	*ptr;

	ptr = *format;
	if (!check_specifier(**format))
		return ;
	info->specifier = *ptr;
	ptr++;
	*format = ptr;
}
