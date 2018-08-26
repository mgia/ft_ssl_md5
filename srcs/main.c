#include "ft_ssl.h"
#include "libft.h"

void	parse_flags(t_info *d, char **av, int ac)
{
	int i;

	i = 1;
	while (++i < ac)
	{
		if (!ft_strcmp("-p", av[i]))
			d->f_p = 1;
		else if (!ft_strcmp("-q", av[i]))
			d->f_q = 1;
		else if (!ft_strcmp("-r", av[i]))
			d->f_r = 1;
		else if (!ft_strcmp("-s", av[i]) && i++)
			d->f_s++;
		else if (av[i][0] == '-')
		{
			ft_printf("unknown option '%s'\n", av[i]);
			exit(1);
		}
		else
			break ;
	}
	d->nb_files = ac - i;
	d->offset = i;
}


void	initialize(t_info *d, char **av, int ac)
{
	d->f_p = 0;
	d->f_q = 0;
	d->f_r = 0;
	d->f_s = 0;
	parse_flags(d, av, ac);
}

const uint32_t md5_s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21
};

const uint32_t md5_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

struct	s_md5_buffer
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
};

typedef struct s_md5_buffer	t_md5;

uint32_t	leftrotate(uint32_t x, uint32_t c)
{
	return (x << c | x >> (32 - c));
}

char		*pad_zeros(char *str)
{
	int i;

	i = ft_strlen(str);
	while (i < 8)
	{
		ft_putchar('0');
		i++;
	}
	return (str);
}

#include "libft.h"


char		*unsigned_itoa_base(uint32_t n, int base)
{
	char	*str;
	char	*tmp;

	str = ft_itoa_base(n, base);
	if (str[0] == '0')
	{
		tmp = str;
		str = ft_strsub(str, 1, ft_strlen(str) - 1);
		free(tmp);
	}
	return (str);
}

void	print_hash(uint32_t *buffer, int size)
{
	char	*tmp;
	int		i;

	i = -1;
	while (++i < size)
	{
		tmp = unsigned_itoa_base(buffer[i], 16);
		ft_putstr(pad_zeros(tmp));
		free(tmp);
	}
}

uint32_t	*init_md5_buffer(void)
{
	uint32_t *buffer;

	buffer = (uint32_t *)malloc(4 * sizeof(uint32_t));
	buffer[0] = 0x67452301;
	buffer[1] = 0xefcdab89;
	buffer[2] = 0x98badcfe;
	buffer[3] = 0x10325476;
	return (buffer);
}

unsigned char	*pad_md5_msg(unsigned char *init_msg, size_t *len)
{
	unsigned char	*msg;
	int		new_len;


	new_len = *len + 1;
	while (new_len % 64 != 56)
		new_len++;
	msg = (unsigned char *)ft_memalloc(new_len + 64);
	ft_memcpy(msg, init_msg, *len);
	msg[*len] = 128;
	msg[new_len] = (unsigned char)(8 * (*len));
	*len = new_len;
	return (msg);
}

void	process_chunk(unsigned char *chunk, uint32_t *block)
{
	t_md5	buf;
	uint32_t	*word;
	uint32_t	f;
	uint32_t	g;
	uint32_t	tmp;
	int		i;

	word = (uint32_t *)chunk;
	buf.a = block[0];
	buf.b = block[1];
	buf.c = block[2];
	buf.d = block[3];
	i = -1;
	while (++i < 64)
	{
		if (i < 16)
		{
			f = (buf.b & buf.c) | ((~buf.b) & buf.d);
			g = i;
		}
		else if (i < 32)
		{
			f = (buf.d & buf.b) | ((~buf.d) & buf.c);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			f = buf.b ^ buf.c ^ buf.d;
			g = (3 * i + 5) % 16;
		}
		else
		{
			f = buf.c ^ (buf.b | (~buf.d));
			g = (7 * i) % 16;
		}
		tmp = buf.d;
		buf.d = buf.c;
		buf.c = buf.b;
		buf.b = buf.b + leftrotate((buf.a + f + md5_k[i] + word[g]), md5_s[i]);
		buf.a = tmp;
	}
	block[0] += buf.a;
	block[1] += buf.b;
	block[2] += buf.c;
	block[3] += buf.d;
}

void	md5(unsigned char *init_msg, size_t len)
{
	uint32_t	*buffer;
	unsigned char	*msg;
	size_t		i;

	buffer = init_md5_buffer();
	msg = pad_md5_msg(init_msg, &len);
	i = 0;
	while (i < len)
	{
		process_chunk(msg + i, buffer);
		i += 64;
	}
	i = -1;
	while (++i < 4)
		buffer[i] = __builtin_bswap32(buffer[i]);
	print_hash(buffer, 4);
	free(buffer);
	free(msg);
}

const uint32_t sha256_k[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

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

uint32_t	*init_sha256_buffer(void)
{
	uint32_t	*buffer;

	buffer = (uint32_t *)ft_memalloc(8 * sizeof(uint32_t));
	buffer[0] = 0x6a09e667;
	buffer[1] = 0xbb67ae85;
	buffer[2] = 0x3c6ef372;
	buffer[3] = 0xa54ff53a;
	buffer[4] = 0x510e527f;
	buffer[5] = 0x9b05688c;
	buffer[6] = 0x1f83d9ab;
	buffer[7] = 0x5be0cd19;
	return (buffer);
}

void	add_big_endian_integer(unsigned char *msg, size_t len, size_t new_len)
{
	msg[new_len / 8 - 8] = (char)(len * 8 >> (8 * 7));
	msg[new_len / 8 - 7] = (char)(len * 8 >> (8 * 6));
	msg[new_len / 8 - 6] = (char)(len * 8 >> (8 * 5));
	msg[new_len / 8 - 5] = (char)(len * 8 >> (8 * 4));
	msg[new_len / 8 - 4] = (char)(len * 8 >> (8 * 3));
	msg[new_len / 8 - 3] = (char)(len * 8 >> (8 * 2));
	msg[new_len / 8 - 2] = (char)(len * 8 >> (8 * 1));
	msg[new_len / 8 - 1] = (char)(len * 8 >> (8 * 0));
}

unsigned char	*pad_sha256_msg(unsigned char *init_msg, size_t *len)
{
	unsigned char	*msg;
	size_t			bit_size;
	size_t			new_len;

	bit_size = *len * 8;
	new_len = ((bit_size + 64) / 512) * 512 + 448 + 64;
	msg = (unsigned char *)ft_memalloc(new_len / 8 + 8);
	ft_memcpy(msg, init_msg, *len);
	msg[*len] = 128;
	add_big_endian_integer(msg, *len, new_len);
	*len = new_len / 8;
	return (msg);
}

uint32_t	right_rotate(uint32_t x, int c)
{
	return (x >> c) | (x << (32 - c));
}

void init_msg_schedule_arr(uint32_t *words, uint32_t m_arr[64])
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

void	init_working_variables(t_sha256 *buf, uint32_t *buffer)
{
	buf->a = buffer[0];
	buf->b = buffer[1];
	buf->c = buffer[2];
	buf->d = buffer[3];
	buf->e = buffer[4];
	buf->f = buffer[5];
	buf->g = buffer[6];
	buf->h = buffer[7];
}

void	append_to_hash(t_sha256 *buf, uint32_t *buffer)
{
	buffer[0] += buf->a;
	buffer[1] += buf->b;
	buffer[2] += buf->c;
	buffer[3] += buf->d;
	buffer[4] += buf->e;
	buffer[5] += buf->f;
	buffer[6] += buf->g;
	buffer[7] += buf->h;
}

void	compression_function(t_sha256 *buf, uint32_t m_arr[64], int i)
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
		temp1 = buf->h + s1 + ch + sha256_k[i] + m_arr[i];
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

void	process_sha256_chunk(unsigned char *chunk, uint32_t *buffer)
{
	uint32_t	*words;
	uint32_t	m_arr[64];
	t_sha256	buf;

	words = (uint32_t *)chunk;
	init_msg_schedule_arr(words, m_arr);
	init_working_variables(&buf, buffer);
	compression_function(&buf, m_arr, 0);
	append_to_hash(&buf, buffer);
}

void	sha256(unsigned char *init_msg, size_t len)
{
	uint32_t		*buffer;
	unsigned char	*msg;
	size_t			i;

	buffer = init_sha256_buffer();
	msg = pad_sha256_msg(init_msg, &len);
	i = 0;
	while (i < len)
	{
		process_sha256_chunk(msg + i, buffer);
		i += 64;
	}
	print_hash(buffer, 8);
	free(msg);
	free(buffer);
}

void	run_hash(char *str, char *hash)
{
	if (!ft_strcmp(hash, "md5"))
		md5((uint8_t *)str, ft_strlen(str));
	else if (!ft_strcmp(hash, "sha256"))
		sha256((unsigned char *)str, ft_strlen(str));
}

#include <stdio.h>
char	*get_str(int fd)
{
	char	*str;
	char	c[2];

	c[1] = 0;
	str = ft_strdup("");
	while (read(fd, c, 1) > 0)
		str = ft_strjoin_rev(c, &str);
	return (str);
}

void	print_stdin(t_info *d, char *hash)
{
	char	*s;

	if (!(s = get_str(0)))
		return ;
	if (d->f_p)
		ft_putstr(s);
	run_hash(s, hash);
	free(s);
}

#include <fcntl.h>

int		get_file(t_info *d, char *name, char *hash)
{
	int		fd;

	if ((fd = open(name, O_RDWR)) < 0)
	{
		ft_printf("ft_ssl: %s: %s: No such file or directory found\n", name, hash);
		return (0);
	}
	d->arg = get_str(fd);
	return (1);
}

char	*ft_str_toupper(char *str)
{
	char	*res;
	int		i;

	res = ft_strdup(str);
	i = -1;
	while (res[++i])
		res[i] = ft_toupper(res[i]);
	return (res);
}

void	print_entry(t_info *d, char *str, char *hash, int file)
{
	char *tmp;

	tmp = ft_str_toupper(hash);
	if (!d->f_q)
	{
		if (file)
			ft_printf("%s (%s) = ", tmp, str);
		else
			ft_printf("%s (\"%s\") = ", tmp, str);
	}
	run_hash(file ? d->arg : str, hash);
	ft_putchar('\n');
	free(tmp);
}

void	print_entry_rev(t_info *d, char *str, char *hash, int file)
{
	run_hash(file ? d->arg : str, hash);
	if (!d->f_q)
	{
		if (file)
			ft_printf(" %s\n", str);
		else
			ft_printf(" \"%s\"\n", str);
	}
}

void	print_arg(t_info *d, char *str, char *hash, int file)
{
	if (file && !get_file(d, str, hash))
		return ;

	if (!d->f_r)
		print_entry(d, str, hash, file);
	else
		print_entry_rev(d, str, hash, file);

	if (file)
		free(d->arg);
}

void	print_args(t_info *d, char **av, int ac)
{
	int		i;

	i = 1;
	while (++i < d->offset)
	{
		if (!ft_strcmp("-s", av[i]) && ++i < d->offset)
			print_arg(d, av[i], av[1], 0);
	}
	while (d->offset < ac)
	{
		print_arg(d, av[d->offset], av[1], 1);
		d->offset++;
	}
}

void	run(t_info *d, char **av, int ac)
{
	initialize(d, av, ac);
	if (d->f_p || !(d->nb_files || d->f_s))
		print_stdin(d, av[1]);
	print_args(d, av, ac);
}

int		kill(char *s)
{
	if (!s)
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
	else
	{
		ft_putstr("ft_ssl:Error: '");
		ft_putstr(s);
		ft_putstr("' is an invalid command.\n\nStandard commands:\n\nMe");
		ft_putstr("ssage Digest commands:\nmd5\nsha256\n\nCipher commands:\n");
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_info	d;

	if (ac == 1)
		return (kill(0));
	if (!ft_strcmp(av[1], "md5") || !ft_strcmp(av[1], "sha256"))
		run(&d, av, ac);
	else
		kill(av[1]);
	return (0);
}
