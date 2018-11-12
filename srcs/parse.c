/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:25:52 by marc              #+#    #+#             */
/*   Updated: 2018/11/08 19:25:53 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	parse_flags(t_info *d, char **av, int ac)
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
