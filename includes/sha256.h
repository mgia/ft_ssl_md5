#ifndef SHA256_H
# define SHA256_H

extern const uint32_t sha256_k[];

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

void		process_sha256_chunk(unsigned char *chunk, uint32_t *block);

#endif
