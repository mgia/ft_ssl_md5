/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_rev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:41:00 by mtan              #+#    #+#             */
/*   Updated: 2018/02/21 17:41:09 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strjoin_rev is modified to free the address pointed by param s1.
*/

char	*ft_strjoin_rev(char const *s1, char **s2)
{
	char	*str;
	char	*tmp;
	size_t	i;
	size_t	j;

	tmp = *s2;
	if (!s1 || !tmp || !(str = ft_strnew(ft_strlen(s1) + ft_strlen(tmp))))
		return (NULL);
	i = -1;
	j = -1;
	while (tmp[++i])
		str[i] = tmp[i];
	while (s1[++j])
		str[i++] = s1[j];
	str[++i] = '\0';
	free(tmp);
	return (str);
}
