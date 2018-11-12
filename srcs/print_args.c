/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:25:56 by marc              #+#    #+#             */
/*   Updated: 2018/11/08 19:25:58 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_entry(t_info *d, char *str, char *hash, int file)
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

static void	print_entry_rev(t_info *d, char *str, char *hash, int file)
{
	run_hash(file ? d->arg : str, hash);
	if (!d->f_q)
	{
		if (file)
			ft_printf(" %s\n", str);
		else
			ft_printf(" \"%s\"\n", str);
	}
	else
		ft_putchar('\n');
}

static void	print_arg(t_info *d, char *str, char *hash, int file)
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

void		print_args(t_info *d, char **av, int ac)
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
};
