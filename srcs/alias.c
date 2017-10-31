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
	int	j;
	j = 0;

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

	char **line_split;

	line_split = ft_split_whitespaces(line);
	ft_strdel(&line);

	while (line_split[j])
	{
		i = 0;
		while (values[i])
		{
			if (!(ft_memcmp(line_split[j], values[i], ft_strlen(line_split[j]))))
			{
				ft_strdel(&line_split[j]);
				line_split[j] = ft_strdup((commands[i]));
			}
			i++;
		}
		j++;
	}
	j = 0;
	line = ft_strnew(0);
	while (line_split[j])
	{
		line = ft_strjoinfree(&line, &line_split[j], 'L');
		line = ft_strjoin(line, " ");
		j++;
	}
	ft_tabdel(line_split);
	close(fd);
	return (line);
}

