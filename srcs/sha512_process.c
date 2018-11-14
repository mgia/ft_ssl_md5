/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:38:42 by marc              #+#    #+#             */
/*   Updated: 2018/11/11 20:38:44 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

static void	init_working_variables(t_sha512 *buf, uint64_t *block)
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

static void	init_msg_schedule_arr(uint64_t *words, uint64_t m_arr[80])
{
	uint64_t	s0;
	uint64_t	s1;
	int			i;

	i = -1;
	while (++i < 16)
		m_arr[i] = __builtin_bswap64(words[i]);
	while (i < 80)
	{
		s0 = right_rotate_64(m_arr[i - 15], 1) ^
				right_rotate_64(m_arr[i - 15], 8) ^ (m_arr[i - 15] >> 7);
		s1 = right_rotate_64(m_arr[i - 2], 19) ^
				right_rotate_64(m_arr[i - 2], 61) ^ (m_arr[i - 2] >> 6);
		m_arr[i] = (m_arr[i - 16] + s0 + m_arr[i - 7] + s1);
		i++;
	}
}

static void	compression_function(t_sha512 *buf, uint64_t m_arr[80], int i)
{
	uint64_t s0;
	uint64_t s1;
	uint64_t maj;
	uint64_t ch;
	uint64_t temp1;

	while (i < 80)
	{
		s0 = right_rotate_64(buf->a, 28) ^ right_rotate_64(buf->a, 34) ^
				right_rotate_64(buf->a, 39);
		maj = (buf->a & buf->b) ^ (buf->a & buf->c) ^ (buf->b & buf->c);
		s1 = right_rotate_64(buf->e, 14) ^ right_rotate_64(buf->e, 18) ^
				right_rotate_64(buf->e, 41);
		ch = (buf->e & buf->f) ^ ((~(buf->e)) & buf->g);
		temp1 = buf->h + s1 + ch + g_sha512_k[i] + m_arr[i];
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

static void	append_to_hash(t_sha512 *buf, uint64_t *block)
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

void		process_sha512_chunk(unsigned char *chunk, uint64_t *block)
{
	uint64_t	*words;
	uint64_t	m_arr[80];
	t_sha512	buf;

	words = (uint64_t *)chunk;
	init_msg_schedule_arr(words, m_arr);
	init_working_variables(&buf, block);
	compression_function(&buf, m_arr, 0);
	append_to_hash(&buf, block);
}
