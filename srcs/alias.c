#include "../includes/minishell.h"
#include <fcntl.h>

char	*find_aliases(char *line)
{
	int i;
	int fd;
	char **values;
	char **commands;
	char *values_line;
	char *commands_line;

	i = 0;
	fd = -1;
	values = NULL;
	commands = NULL;
	values_line = NULL;
	commands_line = NULL;
	fd = open("/Users/lazrossi/Documents/42/minishell/srcs/alias.txt", O_RDONLY);
	get_next_line(fd, &values_line, '\n');
	get_next_line(fd, &commands_line, '\n');
	commands = ft_split_char(commands_line, ',');
	values = ft_split_char(values_line, '_');

	while (values[i])
	{
		if (!(ft_memcmp(line, values[i], ft_strlen(line))))
		{
			ft_strdel(&line);
			line = ft_strdup((commands[i]));
		}
		i++;
	}
	return (line);
}

