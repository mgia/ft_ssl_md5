/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:26:00 by marc              #+#    #+#             */
/*   Updated: 2018/11/08 19:26:04 by marc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_stdin(t_info *d, char *hash)
{
	char	*s;

	if (!(s = get_str(0)))
		return ;
	if (d->f_p)
		ft_putstr(s);
	run_hash(s, hash);
	ft_putchar('\n');
	free(s);
}
