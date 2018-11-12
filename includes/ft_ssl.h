#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include "libft.h"

extern const uint32_t md5_s[];
extern const uint32_t md5_k[];

struct	s_info
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

struct	s_md5_buffer
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	f;
	uint32_t	g;
};

typedef struct s_md5_buffer	t_md5;

/*
** Main functions
*/

void	md5(unsigned char *init_msg, size_t len);
void	sha256(unsigned char *init_msg, size_t len);
void	sha512(unsigned char *init_msg, size_t len);
void	run_hash(char *str, char *hash);
void	add_big_endian_integer(uint8_t *msg, size_t len, size_t new_len);
void	print_hash(uint32_t *buffer, int size);
void	print_hash_64(uint64_t *buffer, int size);
void	print_stdin(t_info *d, char *hash);
void	print_args(t_info *d, char **av, int ac);

/*
** Parse functions
*/

void	initialize(t_info *d, char **av, int ac);

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
