#include "libft.h"

char		*ft_unsigned_itoa_base(uint32_t n, int base)
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
