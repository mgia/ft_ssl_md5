#ifndef SHA512_H
# define SHA512_H

extern const uint64_t sha512_k[];

struct	s_sha512_buffer
{
	uint64_t	a;
	uint64_t	b;
	uint64_t	c;
	uint64_t	d;
	uint64_t	e;
	uint64_t	f;
	uint64_t	g;
	uint64_t	h;
};

typedef struct s_sha512_buffer	t_sha512;

void		process_sha512_chunk(unsigned char *chunk, uint64_t *block);

#endif
