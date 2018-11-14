/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:47:28 by mtan              #+#    #+#             */
/*   Updated: 2018/11/14 13:47:29 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

extern const uint32_t	g_sha256_k[];

struct	s_sha256_buffer
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
};

typedef struct s_sha256_buffer	t_sha256;

void	process_sha256_chunk(unsigned char *chunk, uint32_t *block);

#endif
