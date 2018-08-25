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

static int	ft_get_len(uint32_t n, int base)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static char	*free_str(char *str)
{
	char *tmp;

	tmp = str;
	str = ft_strsub(str, 1, ft_strlen(str) - 1);
	free(tmp);
	return (str);
}

char		*unsigned_itoa_base(uint32_t n, int base)
{
	int		len;
	char	*str;
	char	*cmp;

	cmp = "0123456789abcdef";
	len = ft_get_len(n, base);
	if (n == 0)
		return (ft_strdup("0"));
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len + 1] = 0;
	while (len + 1)
	{
		str[len] = cmp[n % base];
		n = n / base;
		len--;
	}
	if (str[0] == '0')
		str = free_str(str);
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

void	*hi_bzero(void *s, size_t n)
{
	unsigned char	*i;
	size_t			b;

	b = 0;
	i = (unsigned char *)s;
	while (b < n)
	{
		i[b] = '\0';
		b++;
	}
	return (s);
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
	size_t		offset;
	int			i;

	buffer = init_md5_buffer();
	msg = pad_md5_msg(init_msg, &len);
	offset = 0;
	while (offset < len)
	{
		process_chunk(msg + offset, buffer);
		offset += 64;
	}
	i = -1;
	while (++i < 4)
		buffer[i] = __builtin_bswap32(buffer[i]);
	print_hash(buffer, 4);
	free(buffer);
	free(msg);
}

void	exec_sha256(char *init_msg)
{
	ft_printf("hash/sha265/%s", init_msg);
}

void	run_hash(char *str, char *hash)
{
	if (!ft_strcmp(hash, "md5"))
		md5((uint8_t *)str, ft_strlen(str));
	else if (!ft_strcmp(hash, "sha256"))
		exec_sha256(str);
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
		ft_printf("ft_ssl: %s: %s: No such directory found\n", name, hash);
		return (0);
	}
	d->arg = get_str(fd);
	return (1);
}

void	print_entry(t_info *d, char *str, char *hash, int file)
{
	if (!d->f_q)
	{
		if (file)
			ft_printf("%s (%s) = ", hash, str);
		else
			ft_printf("%s (\"%s\") = ", hash, str);
	}
	run_hash(file ? d->arg : str, hash);
	ft_putchar('\n');
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
