/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 18:50:53 by marc              #+#    #+#             */
/*   Updated: 2018/08/26 18:50:54 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	left_rotate(uint32_t x, uint32_t c)
{
	return (x << c | x >> (32 - c));
}

uint32_t	right_rotate(uint32_t x, int c)
{
	return (x >> c) | (x << (32 - c));
}

uint64_t	right_rotate_64(uint64_t x, int c)
{
	return (x >> c) | (x << (64 - c));
}
