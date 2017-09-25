#include "include/libft.h"
#include <stdlib.h>

char	**ft_tabdup(char **str, int size)
{
	int 	i;
	char	**new_tab;

	i = 0;
	new_tab = NULL;
	if (!(new_tab = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (str && str[i])
	{
		if (!(new_tab[i] = ft_strdup(str[i])))
			return (NULL);
		i++;
	}
	while (i <= size)
	{
		new_tab[i] = NULL;
		i++;
	}
	return (new_tab);
}
