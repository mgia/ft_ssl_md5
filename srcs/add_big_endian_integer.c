/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_big_endian_integer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:38:07 by marc              #+#    #+#             */
/*   Updated: 2018/11/11 20:38:09 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Append 64 bit big endian integer to message.
**	Note: len & new_len are bit lengths and msg is 8 bits / unsigned char,
**	thus requires conversion.
*/

void		add_big_endian_integer(uint8_t *msg, size_t len, size_t new_len)
{
	msg[new_len / 8 - 8] = (char)(len * 8 >> (8 * 7));
	msg[new_len / 8 - 7] = (char)(len * 8 >> (8 * 6));
	msg[new_len / 8 - 6] = (char)(len * 8 >> (8 * 5));
	msg[new_len / 8 - 5] = (char)(len * 8 >> (8 * 4));
	msg[new_len / 8 - 4] = (char)(len * 8 >> (8 * 3));
	msg[new_len / 8 - 3] = (char)(len * 8 >> (8 * 2));
	msg[new_len / 8 - 2] = (char)(len * 8 >> (8 * 1));
	msg[new_len / 8 - 1] = (char)(len * 8 >> (8 * 0));
}
