/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:41:00 by mtan              #+#    #+#             */
/*   Updated: 2018/02/21 17:41:09 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strjoin is modified to free the address pointed by param s2.
*/

char	*ft_strjoin(char **s1, char const *s2)
{
	char	*str;
	char	*tmp;
	size_t	i;
	size_t	j;

	tmp = *s1;
	if (!s2 || !tmp || !(str = ft_strnew(ft_strlen(tmp) + ft_strlen(s2))))
		return (NULL);
	i = -1;
	j = -1;
	while (tmp[++i])
		str[i] = tmp[i];
	while (s2[++j])
		str[i++] = s2[j];
	free(tmp);
	return (str);
}
