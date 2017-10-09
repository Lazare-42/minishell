#include "../includes/minishell.h"

void	ft_complete_command(int quote_type, char **command_line)
{
	char    *new_line;
	int		comma_presence;
	int		ret;
	long	buf;

	new_line = ft_strnew(0);
	ft_putstr("dquote> ");
	ret = 1;
	while (ret == 1)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (buf == 127 && new_line[0])
		{
			(new_line)[ft_strlen(new_line) - 1] = ' ';
			ft_putchar('\r');
			ft_putstr("dquote> ");
			ft_putstr(new_line);
			(new_line)[ft_strlen(new_line) - 1] = '\0';
			ft_putchar('\r');
			ft_putstr("dquote> ");
			ft_putstr(new_line);
		}
		else if (buf == '\n')
			break ;
		else if (buf != 127 && buf != KEY_UP && buf != KEY_DOWN && buf != KEY_LEFT && buf != KEY_RIGHT)
		{
			new_line = ft_strjoin(new_line, (char*)&buf);
			ft_putchar('\r');
			ft_putstr("dquote> ");
			ft_putstr(new_line);
		}
	}
	*command_line = ft_strjoinfree(command_line, &new_line, 'B');
	comma_presence = ft_check_commas(*command_line);
	ft_putchar('\n');
	(comma_presence != quote_type) ? ft_recognize_processes(*command_line) :
		ft_complete_command(quote_type, command_line);
}
