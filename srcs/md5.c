/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:25:48 by marc              #+#    #+#             */
/*   Updated: 2018/11/08 19:25:50 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Initialize blocks:
**	Set 4 blocks to initial preset hash values
*/

static uint32_t			*init_buffer(void)
{
	uint32_t *block;

	block = (uint32_t *)malloc(4 * sizeof(uint32_t));
	block[0] = 0x67452301;
	block[1] = 0xefcdab89;
	block[2] = 0x98badcfe;
	block[3] = 0x10325476;
	return (block);
}

/*
**	Pre-processing message:
**	1. Find new length of padded message
**	2. Copy initial message into new message & pad with zeros
**	3. Append single 1 bit to message
**	4. Append original length in bits to message
*/

static unsigned char	*pad_md5_msg(unsigned char *init_msg, size_t *len)
{
	unsigned char	*msg;
	int		new_len;

	new_len = *len + 1;
	while (new_len % 64 != 56)
		new_len++;
	msg = (unsigned char *)ft_memalloc(new_len + 64);
	ft_memcpy(msg, init_msg, *len);
	msg[*len] = 128;
	*(uint32_t*)(msg + new_len) = (8 * (*len));
	*len = new_len;
	return (msg);
}

static void				run_bit_operations(t_md5 *buf, int i)
{
	if (i < 16)
	{
		buf->f = (buf->b & buf->c) | ((~buf->b) & buf->d);
		buf->g = i;
	}
	else if (i < 32)
	{
		buf->f = (buf->d & buf->b) | ((~buf->d) & buf->c);
		buf->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		buf->f = buf->b ^ buf->c ^ buf->d;
		buf->g = (3 * i + 5) % 16;
	}
	else
	{
		buf->f = buf->c ^ (buf->b | (~buf->d));
		buf->g = (7 * i) % 16;
	}
}

/*
**	Processes message in a 512 bit chunk:
**	1. Split chunk into sixteen 32 bit words
**	2. Initialize hash value to buffer
**	3. Perform algorithm for each bit & update buffer
**	4. Add operations result to final blocks
*/

static void				process_chunk(unsigned char *chunk, uint32_t *block)
{
	t_md5		buf;
	uint32_t	*word;
	uint32_t	tmp;
	int			i;

	word = (uint32_t *)chunk;
	buf.a = block[0];
	buf.b = block[1];
	buf.c = block[2];
	buf.d = block[3];
	i = -1;
	while (++i < 64)
	{
		run_bit_operations(&buf, i);
		tmp = buf.d;
		buf.d = buf.c;
		buf.c = buf.b;
		buf.b = buf.b + left_rotate((buf.a + buf.f + md5_k[i] + word[buf.g]), md5_s[i]);
		buf.a = tmp;
	}
	block[0] += buf.a;
	block[1] += buf.b;
	block[2] += buf.c;
	block[3] += buf.d;
}

/*
**	MD5 algorithm produces fixed length 128 bit output from variable length
**	message. The message is padded to be divisble by 512 bits, pre-processed
**	& digested in 512 bit chunks. The result is one-way hashing function that
**	removes the original message while preserving integrity.
*/

void					md5(unsigned char *init_msg, size_t len)
{
	uint32_t		*block;
	unsigned char	*msg;
	size_t			i;

	block = init_buffer();
	msg = pad_md5_msg(init_msg, &len);
	i = 0;
	while (i < len)
	{
		process_chunk(msg + i, block);
		i += 64;
	}
	i = -1;
	while (++i < 4)
		block[i] = __builtin_bswap32(block[i]);
	print_hash(block, 4);
	free(block);
	free(msg);
}
