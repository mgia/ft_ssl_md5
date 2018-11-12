/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:26:06 by marc              #+#    #+#             */
/*   Updated: 2018/11/08 19:26:07 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

/*
**	Initialize blocks:
**	Set 8 blocks to initial preset hash values
*/

static uint32_t	*init_buffer(void)
{
	uint32_t	*block;

	block = (uint32_t *)ft_memalloc(8 * sizeof(uint32_t));
	block[0] = 0x6a09e667;
	block[1] = 0xbb67ae85;
	block[2] = 0x3c6ef372;
	block[3] = 0xa54ff53a;
	block[4] = 0x510e527f;
	block[5] = 0x9b05688c;
	block[6] = 0x1f83d9ab;
	block[7] = 0x5be0cd19;
	return (block);
}

/*
**	Pre-processing message:
**	1. Find new length of padded message (divisible by 512)
**	2. Copy initial message into new message & pad with zeros
**	3. Append single 1 bit to message
**	4. Append 64-bit big endian integer to message
*/

static uint8_t	*pad_sha256_msg(unsigned char *init_msg, size_t *len)
{
	unsigned char	*msg;
	size_t			bit_size;
	size_t			new_len;

	bit_size = *len * 8;
	new_len = ((bit_size + 64) / 512) * 512 + 448 + 64;
	msg = (unsigned char *)ft_memalloc(new_len / 8 + 8);
	ft_memcpy(msg, init_msg, *len);
	msg[*len] = 128;
	add_big_endian_integer(msg, *len, new_len);
	*len = new_len / 8;
	return (msg);
}

/*
**	SHA256 algorithm produces fixed length 256 bit output from variable length
**	message. The message is padded to be divisble by 512 bits, pre-processed
**	& digested in 512 bit chunks. The result is one-way hashing function that
**	removes the original message while preserving integrity. It is built for 32
**	bit words.
*/

void			sha256(unsigned char *init_msg, size_t len)
{
	uint32_t		*buffer;
	unsigned char	*msg;
	size_t			i;

	buffer = init_buffer();
	msg = pad_sha256_msg(init_msg, &len);
	i = 0;
	while (i < len)
	{
		process_sha256_chunk(msg + i, buffer);
		i += 64;
	}
	print_hash(buffer, 8);
	free(msg);
	free(buffer);
}
