/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:40:09 by mtan              #+#    #+#             */
/*   Updated: 2018/11/14 13:40:10 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_toupper(char *str)
{
	char	*res;
	int		i;

	res = ft_strdup(str);
	i = -1;
	while (res[++i])
		res[i] = ft_toupper(res[i]);
	return (res);
}
