#ifndef FT_SSL_H
# define FT_SSL_H

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

#endif
