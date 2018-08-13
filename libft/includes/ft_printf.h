/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:09:53 by mtan              #+#    #+#             */
/*   Updated: 2018/03/12 17:11:33 by mtan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <inttypes.h>

typedef struct	s_data
{
	int		hex;
	int		zero;
	int		minus;
	int		plus;
	int		space;
	int		width;
	int		dot;
	int		precision;
	char	*length;
	char	specifier;
}				t_data;

/*
**	Main functions
*/

int				ft_printf(char *format, ...);
void			handle_mod(char **format, va_list args, int *count);
void			print_format(t_data *info, va_list args, int *count);

/*
**	Parsers
*/
void			parse_printf_flags(t_data *info, char **format);
void			parse_width(t_data *info, char **format);
void			parse_precision(t_data *info, char **format);
void			parse_length(t_data *info, char **format);
void			parse_specifier(t_data *info, char **format);

/*
**	Printers
*/

char			*format_s(t_data *info, va_list args);
char			*format_big_s(t_data *info, va_list args);
char			*format_p(va_list args);
char			*format_d(t_data *info, va_list args);
char			*format_u(t_data *info, va_list args);
char			*format_o(t_data *info, va_list args);
char			*format_x(t_data *info, va_list args);
int				format_null(t_data *info, int *count);
char			*format_c(t_data *info, va_list args, int *count);
char			*format_mod(t_data *info);

/*
**	Utilities
*/

char			*pad_left(char **str, int n, char c);
char			*pad_right(char **str, int n, char c);
char			*slice_left(char **str, int n);
char			*slice_right(char **str, int n);
void			ft_strupper(char *str);

/*
**	Helpers
*/

t_data			*init_data(void);
char			**init_length_specifiers(void);
int				check_flags(t_data *info, char **format);
int				check_length(char **ref, char *str);
int				check_specifier(char c);
intmax_t		get_signed(t_data *info, va_list args);
uintmax_t		get_unsigned(t_data *info, va_list args);

#endif
