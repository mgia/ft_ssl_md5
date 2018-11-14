/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:42:03 by mtan              #+#    #+#             */
/*   Updated: 2018/11/14 13:42:06 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include "libft.h"

struct		s_info
{
	int		f_p;
	int		f_q;
	int		f_r;
	int		f_s;
	int		nb_files;
	int		offset;
	char	*arg;
};

typedef	struct s_info	t_info;

/*
** Main functions
*/

void		md5(unsigned char *init_msg, size_t len);
void		sha256(unsigned char *init_msg, size_t len);
void		sha512(unsigned char *init_msg, size_t len);
void		run_hash(char *str, char *hash);
void		add_big_endian_integer(uint8_t *msg, size_t len, size_t new_len);
void		print_hash(uint32_t *buffer, int size);
void		print_hash_64(uint64_t *buffer, int size);
void		print_stdin(t_info *d, char *hash);
void		print_args(t_info *d, char **av, int ac);

/*
** Parse functions
*/

void		initialize(t_info *d, char **av, int ac);

/*
** Utility functions
*/

int			get_file(t_info *d, char *name, char *hash);
char		*get_str(int fd);
uint32_t	left_rotate(uint32_t x, uint32_t c);
uint32_t	right_rotate(uint32_t x, int c);
uint64_t	right_rotate_64(uint64_t x, int c);
char		*pad_zeros(char *str);
int			kill(char *s);

#endif
