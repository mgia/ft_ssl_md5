/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:26:09 by marc              #+#    #+#             */
/*   Updated: 2018/11/08 19:26:10 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		kill(char *s)
{
	if (!s)
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
	else
	{
		ft_putstr("ft_ssl:Error: '");
		ft_putstr(s);
		ft_putstr("' is an invalid command.\n\nStandard commands:\n\nMe");
		ft_putstr("ssage Digest commands:\nmd5\nsha256\n\nCipher commands:\n");
	}
	return (0);
}
