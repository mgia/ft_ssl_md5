/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 18:49:40 by marc              #+#    #+#             */
/*   Updated: 2018/08/26 18:50:08 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_hex(uint32_t c)
{
	char	base[17];

	ft_strcpy(base, "0123456789abcdef");
	ft_printf("%c%c", base[c / 16], base[c % 16]);
}

void	print_hash(uint32_t *buffer, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		print_hex((buffer[i] & 0xFF000000) >> 8 * 3);
		print_hex((buffer[i] & 0xFF0000) >> 8 * 2);
		print_hex((buffer[i] & 0xFF00) >> 8);
		print_hex(buffer[i] & 0xFF);
	}
}

void	print_hash_64(uint64_t *buffer, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		print_hex((buffer[i] & 0xFF00000000000000) >> 8 * 7);
		print_hex((buffer[i] & 0xFF000000000000) >> 8 * 6);
		print_hex((buffer[i] & 0xFF0000000000) >> 8 * 5);
		print_hex((buffer[i] & 0xFF00000000) >> 8 * 4);
		print_hex((buffer[i] & 0xFF000000) >> 8 * 3);
		print_hex((buffer[i] & 0xFF0000) >> 8 * 2);
		print_hex((buffer[i] & 0xFF00) >> 8);
		print_hex(buffer[i] & 0xFF);
	}
}

void	run_hash(char *str, char *hash)
{
	if (ft_strequ(hash, "md5"))
		md5((unsigned char*)str, ft_strlen(str));
	else if (ft_strequ(hash, "sha256"))
		sha256((unsigned char*)str, ft_strlen(str));
	else if (ft_strequ(hash, "sha512"))
		sha512((unsigned char*)str, ft_strlen(str));
}
