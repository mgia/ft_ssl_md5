/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:38:15 by marc              #+#    #+#             */
/*   Updated: 2018/11/11 20:38:16 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>
#include <sys/stat.h>

char		*get_str(int fd)
{
	char	*str;
	char	c[2];

	c[1] = 0;
	str = ft_strdup("");
	while (read(fd, c, 1) > 0)
		str = ft_strjoin_rev(c, &str);
	return (str);
}

int			get_file(t_info *d, char *name, char *hash)
{
	int			fd;
	struct stat	stat;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		ft_printf("ft_ssl: %s: %s: No such file or directory found\n", name, hash);
		return (0);
	}
	fstat(fd, &stat);
	if (S_ISDIR(stat.st_mode))
	{
		ft_printf("ft_ssl: %s: %s: Is a directory\n", name, hash);
		return (0);
	}
	d->arg = get_str(fd);
	return (1);
}
