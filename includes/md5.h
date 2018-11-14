/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:45:41 by mtan              #+#    #+#             */
/*   Updated: 2018/11/14 13:45:43 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

extern const uint32_t g_md5_s[];
extern const uint32_t g_md5_k[];

struct		s_md5_buffer
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	f;
	uint32_t	g;
};

typedef struct s_md5_buffer	t_md5;

#endif
