#include "ft_ssl.h"
#include "libft.h"

void	parse_flags(t_info *d, char **av, int ac)
{
	int i;

	i = 1;
	while (++i < ac)
	{
		if (ft_strcmp("-p", av[i]) == 0)
			d->f_p = 1;
		else if (ft_strcmp("-q", av[i]) == 0)
			d->f_q = 1;
		else if (ft_strcmp("-r", av[i]) == 0)
			d->f_r = 1;
		else if (ft_strcmp("-s", av[i]) == 0)
		{
			i++;
			d->f_s++;
		}
		else
			break ;
	}
	d->nb_files = ac - i;
}

void	initialize(t_info *d, char **av, int ac)
{
	d->f_p = 0;
	d->f_q = 0;
	d->f_r = 0;
	d->f_s = 0;
	parse_flags(d, av, ac);
}

#include <unistd.h>
#include <stdlib.h>


void	exec_md5(t_info *d, char *init_msg)
{
	d->nb_files = d->nb_files;
	ft_printf("%s", init_msg);
}

// void	exec_sha256(t_info *d, char *init_msg)
// {
//
// }

void	run_hash(t_info *d, char *str, char *hash)
{
	if (!ft_strcmp(hash, "md5"))
		exec_md5(d, str);
	// else if (!ft_strcmp(hash, "sha256"))
		// exec_sha256(info, str);
}

char	*get_stdin(void)
{
	char	*str;
	char	c[2];

	c[1] = 0;
	str = ft_strdup("");
	while (read(0, c, 1) > 0)
		str = ft_strjoin(&str, c);
	return (str);
}

void	print_stdin(t_info *d, char *hash)
{
	char	*s;

	s = get_stdin();
	if (d->f_p)
		ft_putstr(s);
	run_hash(d, s, hash);
	free(s);
}

void	run(t_info *d, char **av, int ac)
{
	initialize(d, av, ac);
	if (d->f_p || !d->nb_files)
		print_stdin(d, av[1]);
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
