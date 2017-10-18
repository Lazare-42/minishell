#include "../includes/minishell.h"

char	*find_aliases(char *line)
{
	int i;

	i = 0;
	char *values[] = {"work", "Makefile", "m", "norm", NULL};
	char *commands[] = {"cd /Users/lazrossi/Documents/42/minishell", 
		"sh makemf.sh minishell", "./minishell", "norminette", NULL};
	while (values[i])
	{
		if (!(ft_memcmp(line, values[i], ft_strlen(values[i]))))
		{
			ft_strdel(&line);
			line = ft_strdup((commands[i]));
		}
		i++;
	}
	return (line);
}

