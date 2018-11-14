/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:38:34 by marc              #+#    #+#             */
/*   Updated: 2018/11/11 20:38:37 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

/*
**	Initialize blocks:
**	Set 8 blocks to initial preset hash values
*/

static uint64_t	*init_buffer(void)
{
	uint64_t	*block;

	block = (uint64_t *)ft_memalloc(8 * sizeof(uint64_t));
	block[0] = 0x6a09e667f3bcc908;
	block[1] = 0xbb67ae8584caa73b;
	block[2] = 0x3c6ef372fe94f82b;
	block[3] = 0xa54ff53a5f1d36f1;
	block[4] = 0x510e527fade682d1;
	block[5] = 0x9b05688c2b3e6c1f;
	block[6] = 0x1f83d9abfb41bd6b;
	block[7] = 0x5be0cd19137e2179;
	return (block);
}

/*
**	Pre-processing message:
**	1. Find new length of padded message (divisible by 512)
**	2. Copy initial message into new message & pad with zeros
**	3. Append single 1 bit to message
**	4. Append 64-bit big endian integer to message
*/

static uint8_t	*pad_sha512_msg(unsigned char *init_msg, size_t *len)
{
	unsigned char	*msg;
	size_t			bit_size;
	size_t			new_len;

	bit_size = *len * 8;
	new_len = ((bit_size + 128) / 1024) * 1024 + 1024;
	msg = (unsigned char *)ft_memalloc(new_len / 8);
	ft_memcpy(msg, init_msg, *len);
	msg[*len] = 128;
	add_big_endian_integer(msg, *len, new_len);
	*len = new_len / 8;
	return (msg);
}

/*
**	SHA512 algorithm produces fixed length 512 bit output from variable length
**	message. The message is padded to be divisble by 512 bits, pre-processed
**	& digested in 512 bit chunks. The result is one-way hashing function that
**	removes the original message while preserving integrity. It is built for 64
**	bit words.
*/

void			sha512(unsigned char *init_msg, size_t len)
{
	uint64_t		*buffer;
	unsigned char	*msg;
	size_t			i;

	buffer = init_buffer();
	msg = pad_sha512_msg(init_msg, &len);
	i = 0;
	while (i < len)
	{
		process_sha512_chunk(msg + i, buffer);
		i += 128;
	}
	print_hash_64(buffer, 8);
	free(msg);
	free(buffer);
}
