/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:38:27 by marc              #+#    #+#             */
/*   Updated: 2018/11/11 20:38:31 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

static void	init_working_variables(t_sha256 *buf, uint32_t *block)
{
	buf->a = block[0];
	buf->b = block[1];
	buf->c = block[2];
	buf->d = block[3];
	buf->e = block[4];
	buf->f = block[5];
	buf->g = block[6];
	buf->h = block[7];
}

static void	init_msg_schedule_arr(uint32_t *words, uint32_t m_arr[64])
{
	uint32_t	s0;
	uint32_t	s1;
	int			i;

	i = -1;
	while (++i < 16)
		m_arr[i] = __builtin_bswap32(words[i]);
	while (i < 64)
	{
		s0 = right_rotate(m_arr[i - 15], 7) ^ right_rotate(m_arr[i - 15], 18) ^
				(m_arr[i - 15] >> 3);
		s1 = right_rotate(m_arr[i - 2], 17) ^ right_rotate(m_arr[i - 2], 19) ^
				(m_arr[i - 2] >> 10);
		m_arr[i] = (m_arr[i - 16] + s0 + m_arr[i - 7] + s1);
		i++;
	}
}

static void	compression_function(t_sha256 *buf, uint32_t m_arr[64], int i)
{
	uint32_t s0;
	uint32_t s1;
	uint32_t maj;
	uint32_t ch;
	uint32_t temp1;

	while (i < 64)
	{
		s1 = right_rotate(buf->e, 6) ^ right_rotate(buf->e, 11) ^
				right_rotate(buf->e, 25);
		ch = (buf->e & buf->f) ^ ((~(buf->e)) & buf->g);
		temp1 = buf->h + s1 + ch + g_sha256_k[i] + m_arr[i];
		s0 = right_rotate(buf->a, 2) ^ right_rotate(buf->a, 13) ^
				right_rotate(buf->a, 22);
		maj = (buf->a & buf->b) ^ (buf->a & buf->c) ^ (buf->b & buf->c);
		buf->h = buf->g;
		buf->g = buf->f;
		buf->f = buf->e;
		buf->e = buf->d + temp1;
		buf->d = buf->c;
		buf->c = buf->b;
		buf->b = buf->a;
		buf->a = temp1 + s0 + maj;
		i++;
	}
}

static void	append_to_hash(t_sha256 *buf, uint32_t *block)
{
	block[0] += buf->a;
	block[1] += buf->b;
	block[2] += buf->c;
	block[3] += buf->d;
	block[4] += buf->e;
	block[5] += buf->f;
	block[6] += buf->g;
	block[7] += buf->h;
}

/*
**	Processes message in a 512 bit chunk:
**	1. Create a message schedule array of 32 bit words
**	2. Initialize hash values to buffer
**	3. Perform compression algorithm for each bit & update buffer
**	4. Add operations result to final blocks
*/

void		process_sha256_chunk(unsigned char *chunk, uint32_t *block)
{
	uint32_t	*words;
	uint32_t	m_arr[64];
	t_sha256	buf;

	words = (uint32_t *)chunk;
	init_msg_schedule_arr(words, m_arr);
	init_working_variables(&buf, block);
	compression_function(&buf, m_arr, 0);
	append_to_hash(&buf, block);
}
