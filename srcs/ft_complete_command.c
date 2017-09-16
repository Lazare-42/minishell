#include "../includes/minishell.h"

void	ft_complete_command(int quote_type, char *command_line)
{
	char	*new_line;
	int		comma_presence;

	new_line = NULL;
	ft_putstr("dquote> ");
	command_line[ft_strlen(command_line) - 1] = '\0';
	while ((new_line = ft_file_to_string()) || (!ft_strlen(new_line)))
	{
		if (ft_strchr(new_line, '\n'))
			break;
	}
	comma_presence = ft_check_commas(new_line);
	new_line = ft_strjoinfree(&command_line, &new_line, 'R');
	(comma_presence == quote_type) ? ft_recognize_processes(new_line) :
		ft_complete_command(quote_type, new_line);
}
