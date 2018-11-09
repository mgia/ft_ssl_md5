#include "libft.h"

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
