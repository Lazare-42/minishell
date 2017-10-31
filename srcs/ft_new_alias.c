#include "../includes/minishell.h"
#include <fcntl.h>

void	ft_new_alias(char **new_values)
{
	int fd;
	char *alias_name;
	char *alias_value;
	int i;

	i = 0;
	while (new_values[i])
		i++;
	if (i != 2)
	{
		ft_putstr("alias : 2 arguments expected\n");
		return ;
	}

	fd = open("/Users/lazrossi/Documents/42/minishell/srcs/alias.txt", O_RDWR);
	get_next_line(fd, &alias_name, '\n');
	get_next_line(fd, &alias_value, '\n');
	close(fd);

	alias_name = ft_strjoin(alias_name, "_");
	alias_name = ft_strjoin(alias_name, new_values[0]);
	alias_name = ft_strjoin(alias_name, "\n");

	alias_value = ft_strjoin(alias_value, ",");
	alias_value = ft_strjoin(alias_value, new_values[1]);
	alias_value = ft_strjoin(alias_value, "\n");
	fd = open("/Users/lazrossi/Documents/42/minishell/srcs/alias.txt", O_RDWR);
	write(fd, alias_name, ft_strlen(alias_name));
	write(fd, alias_value, ft_strlen(alias_value));
	close(fd);
}
