/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:02:24 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:02:27 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pad_left(char **str, int n, char c)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	char	*tmp2;

	i = 0;
	j = 0;
	tmp2 = *str;
	len = ft_strlen(*str);
	if (n <= len)
		return (*str);
	tmp = ft_strnew(n);
	while (i < (n - len))
		tmp[i++] = c;
	while (i < n)
		tmp[i++] = tmp2[j++];
	free(tmp2);
	return (tmp);
}

char	*pad_right(char **str, int n, char c)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	char	*tmp2;

	i = 0;
	j = 0;
	tmp2 = *str;
	len = ft_strlen(*str);
	if (n <= len)
		return (*str);
	tmp = ft_strnew(n);
	while (tmp2[j])
		tmp[i++] = tmp2[j++];
	while (i < n)
		tmp[i++] = c;
	free(tmp2);
	return (tmp);
}

char	*slice_left(char **str, int n)
{
	int		i;
	int		len;
	char	*tmp;
	char	*tmp2;

	tmp2 = *str;
	i = 0;
	len = ft_strlen(tmp2);
	if (n >= len)
		return ("");
	tmp = ft_strnew(len - n);
	while (tmp2[n])
		tmp[i++] = tmp2[n++];
	free(tmp2);
	return (tmp);
}

char	*slice_right(char **str, int n)
{
	int		i;
	int		len;
	char	*tmp;
	char	*tmp2;

	tmp2 = *str;
	i = 0;
	len = ft_strlen(tmp2);
	if (n >= len)
		return ("");
	tmp = ft_strnew(len - n);
	while (i < (len - n))
	{
		tmp[i] = tmp2[i];
		i++;
	}
	free(tmp2);
	return (tmp);
}
