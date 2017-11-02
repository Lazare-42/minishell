#include "../includes/minishell.h"
#include <fcntl.h>

static char	**ft_tab_with_alias(char **values, char **commands, char **line_split)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (line_split[j])
	{
		i = 0;
		while (values[i])
		{
			if (!(ft_memcmp(line_split[j], values[i], ft_strlen(line_split[j]))) 
						&& ft_strlen(line_split[j]) == ft_strlen(values[i]))
			{
				ft_strdel(&line_split[j]);
				if (commands[i])
				line_split[j] = ft_strdup((commands[i]));
				i = 0;
				j = 0;
			}
			i++;
		}
		j++;
	}
	return (line_split);
}

static char *ft_used_tabdel(char **commands, char **values, char **line_split, char *line)
{
	if (commands)
		ft_tabdel(commands);
	if (values)
		ft_tabdel(values);
	if (line_split)
		ft_tabdel(line_split);
	return (line);
}

static char	*ft_launch_replacement(char *line, char **values, char **commands, char **line_split)
{
	int 	j;
	char	*space_str;

	j = 0;
	ft_memdel((void**)&line);
	space_str = NULL;
	if (!(line = ft_strnew(0)) || !(space_str = ft_strnew(1)))
		return (ft_used_tabdel(commands, values, line_split, line));
	space_str[0] = ' ';
	line_split = ft_tab_with_alias(values, commands, line_split);
	while (line_split[j])
	{
		line = ft_strjoinfree(&line, &line_split[j], 'L');
		line = ft_strjoinfree(&line, &space_str, 'L');
		j++;
	}
	ft_memdel((void**)&space_str);
	return (ft_used_tabdel(commands, values, line_split, line));
}

static char	*ft_malloc_for_alias(char *values_line, char *commands_line, char *line)
{
	char	**values;
	char	**commands;
	char 	**line_split;

	values = NULL;
	commands = NULL;
	line_split = NULL;
	if (!(commands = ft_split_char(commands_line, ',')) || 
			!(values = ft_split_char(values_line, '_')) ||
			!(line_split = ft_split_whitespaces(line)))
		return (ft_used_tabdel(commands, values, line_split, line));
	return (ft_launch_replacement(line, values, commands, line_split));
}

char	*find_aliases(char *line)
{
	int		fd;
	char	*values_line;
	char	*commands_line;
	int		j;

	j = 0;
	fd = -1;
	values_line = NULL;
	commands_line = NULL;

	fd = open("/Users/lazrossi/Documents/42/minishell/srcs/alias.txt",
			O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Unable to open alias.txt\n");
		return (line);
	}
	if (!get_next_line(fd, &values_line, '\n') ||
			!get_next_line(fd, &commands_line, '\n'))
	{
		ft_putstr("Unable to read alias.txt with GNL\n");
		return (line);
	}
	close(fd);
	return (ft_malloc_for_alias(values_line, commands_line, line));
}
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 16:30:57 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/07 16:00:34 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_recognize_builtin_command(char *str)
{
	char	*commands[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit", "chdir", "alias", NULL};
	int		i;

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(commands[i], str) == 0)
				return (i);
		i++;
	}
	return (-1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:26:55 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/06 13:51:33 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"

extern	char	**environ;

static char	**ft_add_command_to_path(char **possible_path, char	*arg)
{
	int		i;
	char	*slash;

	i = 0;
	slash = "/";
	while (possible_path[i])
	{
		possible_path[i] = ft_strjoinfree(&possible_path[i], &slash, 'L');
		possible_path[i] = ft_strjoinfree(&possible_path[i], &arg, 'L');
		i++;
	}
	return (possible_path);
}

char	**ft_find_prog_path(char *arg)
{
	int		i;
	char	*tmp;
	char	**possible_program_path;

	i = 0;
	possible_program_path = NULL;
	while (environ[i] && ft_memcmp(environ[i], "PATH=", 5) != 0)
		i++;
	if (!(environ[i]))
		return (NULL);
	tmp = &environ[i][5];
	possible_program_path = ft_strsplit(tmp, ':');
	return (ft_add_command_to_path(possible_program_path, arg));
}

char	*ft_find_my_prog_path(char *arg)
{
	int		i;
	char	*path;
	char	*tmp_arg;

	i = 0;
	while (environ[i] && ft_memcmp(environ[i], "PWD=", 4) != 0)
		i++;
	path = &environ[i][4];
	if (arg && arg[0] == '.' && arg[1] == '/')
	{
		tmp_arg = &arg[1];
		path = ft_strjoin(path, tmp_arg);
	}
	else if (arg)
	{
		tmp_arg = ft_strjoin("/", arg);
		path = ft_strjoinfree(&path, &tmp_arg, 'R');
	}
	return (path);
}
#include "../includes/minishell.h"

char	*ft_advance_string_for_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[i] != '\'')
				i++;
			return (&str[i]);
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			while (str[i] != '\"')
				i++;
			return (&str[i]);
		}
		i++;
	}
	return (str);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:20:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/12 13:08:05 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"
#include <unistd.h>

extern char **environ;

void	ft_call_to_chdir(char *str, char *arg)
{
	char	path[1025];
	char 	*tmp;
	char	*path_var = "PWD=";
	char	*setenv_path[2];

	tmp = NULL;
	if (chdir(str))
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		tmp = getcwd(path, 1024);
		path_var = ft_strjoin(path_var, tmp);
		setenv_path[0] = path_var;
		setenv_path[1] = NULL;
		environ = ft_setenv(setenv_path, ft_tabsize(environ), environ);
		ft_strdel(&path_var);
	}
}

int		ft_change_dir(char *str)
{
	char	tmp[1025];
	int		i;

	i = 0;
	if (!str)
	{
		while (environ[i] && ft_memcmp(environ[i], "HOME=", 5))
			i++;
		ft_call_to_chdir(&environ[i][5], str);
		return (0);
	}
	if (str && str[0] != '/')
	{
		getcwd(tmp, 1024);
		ft_strcat(tmp, "/");
		ft_strcat(tmp, str);
		ft_call_to_chdir(tmp, str);
		return (0);
	}
	if (!str[1])
		chdir("/");
	ft_call_to_chdir(str, str);
	return (0);
}

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
char extern **environ;

#include "../includes/minishell.h"

void	ft_print_corresponding_variable(char *str)
{
	size_t	i;
	int		j;

	i = ft_strlen(str);
	j = 0;
	str++;
	if (str)
	{
		while (environ[j] && (ft_memcmp(environ[j], str, i - 1) || environ[j][i - 1] != '='))
			j++;
		if (environ[j])
			ft_putstr(&environ[j][i]);
	}
}

void	ft_parse(char **str)
{
	int 	i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != '$')
		{
			ft_putchar(str[i][j]);
			j++;
		}
		if (str[i][j] && str[i][j] == '$')
			ft_print_corresponding_variable(&str[i][j]);
		ft_putchar(' ');
		i++;
	}
}

void	ft_echo(char **str)
{
	if (!(ft_memcmp(str[0], "-n", 2)))
		ft_parse(&str[1]);
	else
	{
		ft_parse(str);
		ft_putchar('\n');
	}
}
#include "../includes/minishell.h"

extern char **environ;

static void ft_launch_forkk(char **new_environ, char **args)
{
	ft_launch_processes(args, new_environ);
}

static void ft_env_options(char **args)
{
	int		i;
	int		j;
	char	**new_environ;

	i = 0;
	j = 0;
	new_environ = ft_tabdup(environ, ft_tabsize(environ));
	while (args[i] && args[i][0] && args[i][0] == '-')
	{
		if (args[i][0] && args[i][0] == '-' && (!args[i][1]))
					new_environ = NULL;
		while (args[i][j])
		{
			if (args[i][j] == 'i')
					new_environ = NULL;
			j++;
		}
		i++;
	}
	j = 0;
	while (args[i] && ft_strchr(args[i], '='))
	{
		new_environ = ft_setenv(&args[i], ft_new_environ_size(&args[i], new_environ), new_environ);
		i++;
	}
	if (args[i])
		ft_launch_forkk(new_environ, &args[i]);
}

void	ft_env(char **args)
{
	if (!(args[0]))
		return (ft_put_env());
	ft_env_options(args);
}
#include "../includes/minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>
# include <stdlib.h>

extern char		**environ;

static void	ft_launch_ext_command(char **arguments, char **environ_to_use)
{
	int 	i;
	char 	**possible_path;
	char	*my_prog_path;
	int		forkk;

	i = 0;
	forkk = 1;
	possible_path = NULL;
	my_prog_path = NULL;
	forkk = fork();
	if (!(forkk))
	{
		possible_path = ft_find_prog_path(arguments[0], environ_to_use);
		(!possible_path) ? ft_put_command_errors(arguments[0]) : 0;
		while (possible_path[i] && execve(possible_path[i], arguments, environ_to_use) == -1)
			i++;
		if (!possible_path[i])
		{
			my_prog_path = ft_find_my_prog_path(arguments[0]);
				if (execve(my_prog_path, arguments, environ_to_use) == -1)
					ft_put_command_errors(arguments[0]);
		}
		exit(0);
	}
	if (forkk)
		wait(&forkk);
	(possible_path) ? ft_tabdel(possible_path) : 0;
}

static void	ft_launch_builtin_processes(int command_number, char **arguments)
{
	if (arguments[1])
	{
		(command_number == 0) ? ft_echo(&arguments[1]): 0;
		(command_number == 1 ) ? ft_change_dir(arguments[1]) : 0;
		(command_number == 6 ) ? ft_change_dir(arguments[1]) : 0;
		(command_number == 7) ? ft_new_alias(&arguments[1]) : 0;
	}
	(command_number == 2) ? ft_sort_setenv(&arguments[1]): 0;
	(command_number == 3) ? ft_unsetenv(&arguments[1]) : 0;
	(command_number == 4) ? ft_env(&arguments[1]) : 0;
	(command_number == 5) ? ft_putstr("exit\n") : 0;
	(command_number == 5) ? exit (1): 0;
}

void	ft_launch_processes(char **arguments, char **environ_to_use)
{
	int 	command_number;

	if (arguments[0])
	{
		if ((command_number = ft_recognize_builtin_command(arguments[0])) != -1)
			ft_launch_builtin_processes(command_number, arguments);
		else (ft_launch_ext_command(arguments, environ_to_use));
	}
	ft_print_current_directory();
}
#include "../includes/minishell.h"

void	ft_advance_lst_to(t_arg *first, t_arg **to_find, char **line, int line_len)
{
	t_arg *tmp;

	tmp = first;
	while (tmp && ft_memcmp(*line, first->arg, line_len))
		tmp = tmp->next;
	if (tmp)
		*to_find = first;
}

void	ft_retreat_lst_to(t_arg *first, t_arg **to_find, char **line, int line_len)
{
	if (!ft_memcmp(*line, first->arg, line_len) && first->line_pos == 1)
		*(to_find) = first;
}
#include "../includes/minishell.h"
#include <fcntl.h>

void	ft_new_alias(char **new_values)
{
	int fd;
	char *alias_name;
	char *alias_value;

	if (!(ft_put_alias_errors(new_values)))
		return ;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:09:39 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/06 14:44:07 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/include/libft.h"

void	ft_put_command_errors(char *str)
{
	int i;

	i = 0;
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar('\n');
}

static int 	ft_return_alias_errors(int i, int underscore_nbr)
{
	if (i != 2 || underscore_nbr)
	{
		if (i != 2)
		{
			ft_putstr("alias : 2 arguments expected, you have ");
			ft_putnbr(i);
			ft_putstr(". \nIf this appears to be an error, you might want");
			ft_putstr(" to check if you are not using a redundant alias.\n");
		}
		if (underscore_nbr)
		{
			ft_putstr("Underscores separate aliases in alias.txt ");
			ft_putstr("Please remove any underscore of the alias\n");
		}
		return (0);
	}
	return (1);
}

int		ft_put_alias_errors(char **str)
{
	int i;
	int j;
	int	underscore_nbr;

	i = 0;
	underscore_nbr = 0;
	j = -1;
	while (str[i])
		i++;
	while (str[0][++j])
		if (str[0][j] == '_')
			underscore_nbr++;
	return (ft_return_alias_errors(i, underscore_nbr));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:37:30 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/07 13:20:36 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <sys/xattr.h>
#include <sys/dir.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

static char *get_last_part(char *tmp)
{
	int i;
	int	k;

	i = 0;
	k = 0;
	if (tmp)
		i = ft_strlen(tmp);
	k = i;
	if (i > 1)
		i--;
	while (tmp[i] != '/')
		i--;
	if (i > 1)
		i++;
	return (&tmp[i]);
}

static void ft_putstr_noret(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		ft_putchar(str[i]);
		i++;
	}
}

static void ft_print_git()
{
	DIR				*dir;
	struct dirent	*dent;
	char			*buf;
	char			*path;
	int				fd;
	int				ret;

	path = NULL;
	buf = ft_strnew(1025);
	if ((dir = opendir(".git")))
	{
		while (dir && (dent = readdir(dir)))
		{
			if (ft_memcmp(dent->d_name, "HEAD", 4) == 0)
			{
				path = ft_strjoin(getcwd(dent->d_name, 1024), "/.git/HEAD");
				fd = open(path, O_RDONLY);
				ret = read(fd, buf, 1024);
				(ret != -1 ) ? buf[ft_strlen(buf) - 1] = '\0' : 0;
				ft_putstr("[git@]");
				ft_putstr_noret(get_last_part(buf));
				(path) ? ft_strdel(&path) : 0;
			}
		}
		closedir(dir);
	}
	(buf) ? ft_strdel(&buf) : 0;
}

void		ft_print_current_directory()
{
	char	path[1025];
	char 	*tmp;
	int		i;

	i = 0;
	tmp = getcwd(path, 1024);
	ft_putstr("\e[0;91m");
	ft_putchar('/');
	if (tmp)
		ft_putstr(get_last_part(tmp));
	else
		ft_putstr_fd("! getcwd() failed, unknown shell location !", 2);
	ft_putstr("\e[0m");
	ft_putstr("\e[0;90m");
	ft_print_git();
	ft_putstr("\\ ");
	ft_putstr("\e[0m");
}
#include "../includes/minishell.h"

extern char **environ;

void	ft_put_env()
{
	ft_putabs(environ, '\n');
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:20:48 by antoipom          #+#    #+#             */
/*   Updated: 2017/09/07 17:13:19 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

char  *old_line;
t_arg *to_find;
t_arg *first_arg;

int	set_non_canonical_input()
{
	struct termios termios_cpy;

	if 	(tcgetattr(0, &termios_cpy) != 0)
		return (0);
	termios_cpy.c_cc[VMIN] = 1;
	termios_cpy.c_cc[VTIME] = 0;
	termios_cpy.c_lflag &= (IGNBRK);
	termios_cpy.c_lflag &= (ICANON);
	if (tcsetattr(0, TCSANOW, &termios_cpy) != 0)
		return (0);
	return (1);
}

void ft_replace_content(char *line)
{
	ft_putchar('\r');
	ft_print_current_directory();
	(line) ? ft_putstr(line) : 0;
}

int 	ft_check_input_for_ctrl_keys(char **line, int buf, t_arg *first_arg)
{
	t_arg *tmp;

	tmp = NULL;
	if (buf == KEY_UP)
	{
		if (first_arg && old_line)
		{
			(to_find && tmp != to_find) ? tmp = to_find : 0;
			if (to_find && !ft_memcmp(*line, to_find->arg, ft_strlen(old_line)) && to_find->line_pos == 1)
			{
				ft_putchar('\r');
				ft_print_current_directory();
				ft_putwhites(ft_strlen(to_find->arg));
			}
			ft_advance_lst_to(first_arg, &to_find, &old_line, ft_strlen(old_line));
			(to_find) ? *line = to_find->arg : 0;
			(to_find) ? to_find->line_pos = 1 : 0;
		}
		return (0);
	}
	if (buf == KEY_DOWN)
	{
		if (first_arg && to_find)
		{
			to_find->line_pos = 2;
			ft_putchar('\r');
			ft_print_current_directory();
			ft_putwhites(ft_strlen(to_find->arg));
			to_find = NULL;
			ft_retreat_lst_to(first_arg, &to_find, &old_line, ft_strlen(old_line));
			*line = (to_find) ? to_find->arg : ft_strnew(0);
			*line = (!to_find && tmp) ? tmp->arg : *line;
			return (0);
		}
		return (0);
	}
	if (buf == KEY_LEFT)
	{
		return (1);
	}
	if (buf == KEY_RIGHT)
	{
		return (1);
	}
	return (1);
}

static int ft_check_input_for_special_input(char **line, int buf, t_arg *first_arg)
{
	if (line && *line && **line && buf == 127)
	{
		(*line)[ft_strlen(*line) - 1] = ' ';
		ft_putchar('\r');
		ft_print_current_directory();
		ft_putstr(*line);
		(*line)[ft_strlen(*line) - 1] = '\0';
		ft_replace_content(*line);
	}
	if (buf == 127)
		return (0);
	if (*line && buf == '\n')
	{
		to_find = NULL;
		old_line = NULL;
		(old_line) ? ft_strdel(&old_line) : NULL;
		(**line) ? first_arg = ft_store_args(*line, first_arg) : 0;
		ft_putchar('\n');
		(**line) ? ft_look_inside(*line) : 0;
		*line = ft_strnew(0);
		return (0);
	}
	return (ft_check_input_for_ctrl_keys(line, buf, first_arg));
}


char	*ft_file_to_string()
{
	long  buf;
	char  *line;
	int ret;


	ret = 1;
	old_line = NULL;
	to_find = NULL;
	first_arg = NULL;
	if (!(line = ft_strnew(0)))
		return (NULL);
	if (!(set_non_canonical_input()))
		return (NULL);
	first_arg = ft_store_args(line, first_arg);
	while (ret)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (ft_check_input_for_special_input(&line, buf, first_arg)) 
			line = ft_strjoin(line, (char*)&buf);
		(line) ? ft_replace_content(line) : 0;
		(buf != KEY_UP && buf != KEY_DOWN && line) ? old_line = ft_strdup(line) : 0;
	}
	return (NULL);
}
#include "../includes/minishell.h"

extern char** environ;

static size_t ft_pathlen(char *str)
{
	size_t i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (str[i])
		return (i);
	else
		return (0);
}

static char	*ft_add_env_var(char *env_location, char *new_env)
{
	if (env_location)
		ft_strdel(&env_location);
	env_location = ft_strdup(new_env);
	return (env_location);
}

int	ft_new_environ_size(char **args, char **environ_tocpy)
{
	int i;
	int j;

	i = 0;
	j = 0;
	j = ft_tabsize(environ_tocpy);
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			j++;
		i++;
	}
	return (j + 1);
}

char	**ft_setenv(char **args, int new_environ_size, char **environ_tocpy)
{
	int		i;
	int		j;
	size_t	var_len;
	char	**new_env;

	i = -1;
	var_len = 0;
	new_env = ft_tabdup(environ_tocpy, new_environ_size);
	(environ_tocpy) ? ft_tabdel(environ_tocpy) : 0;
	while (args[++i])
	{
		j = 0;
		var_len = ft_pathlen(args[i]);
		while(var_len && new_env[j] && 
		(((new_env[j][var_len]
		   != '=' || ft_memcmp(args[i], new_env[j], var_len))) 
		 || (new_env[j] && var_len >= ft_strlen(new_env[j]))))
			j++;
		if (var_len)
			new_env[j] = ft_add_env_var(new_env[j], args[i]);
	}
	return (new_env);
}

void	ft_sort_setenv(char	**args)
{
	int i;

	i = 0;
	if (!args[0])
	{
		(ft_putabs(environ, '\n'));
		return ;
	}
	else if (!ft_isalpha(args[0][0]))
		ft_putstr_fd("setenv: Variable name must begin with a letter.\n", 2);
	else if (args && args[0])
		environ = ft_setenv(args, ft_new_environ_size(args, environ), environ);
}
#include "minishell.h"
#include <stdlib.h> 
#include <fcntl.h>

static void	ft_place_element_in_tern_tree(t_arg **first, t_arg *new)
{
	new->next = *first;
	(*first)->previous = new;
	*first = new;
}

static t_arg	*new_arg(char *line)
{
	t_arg 	*new;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	new->arg = ft_strdup(line);
	new->previous = NULL;
	new->next = NULL;
	new->line_pos = 2;
	return (new);
}

static t_arg	*ft_store_command_historic(char *line, t_arg *first)
{
	int		fd;
	char	*historic_commands;
	t_arg	*new;	

	fd = -1;
	historic_commands = NULL;
	new = NULL;
	fd = open("/Users/lazrossi/Documents/42/minishell/historic.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Unable to open or find the command historic file.\n");
		ft_print_current_directory();
		return (new_arg(line));
	}
	else while (get_next_line(fd, &historic_commands, '\n'))
	{
		if (!first)
			first = new_arg(historic_commands);
		new = new_arg(historic_commands);
		if (new)
			ft_place_element_in_tern_tree(&first, new);
	}
	close(fd);
	return (first);
}

t_arg	*ft_store_args(char	*line, t_arg *first)
{
	t_arg	*new;

	new = NULL;
	if (!first)
		return (ft_store_command_historic(line, first));
	new = new_arg(line);
	if (new)
		ft_place_element_in_tern_tree(&first, new);
	return (first);
}
extern char **environ;

#include "../includes/minishell.h"

static void	ft_del_one_environ_var(char *str)
{
	int i;
	int	to_del;

	i = 0;
	to_del = 1;
	while (environ[i] && ft_strcmp(str, environ[i]))
		i++;
	while (environ[i])
	{
		if (to_del)
		{
			ft_strdel(&environ[i]);
			to_del = 0;
		}
		environ[i] = environ[i + 1];
		i++;
	}
}

void	ft_unsetenv(char **str)
{
	int i;
	int j;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		len = ft_strlen(str[i]);
		j = 0;
		while(environ[j] && (environ[j][len] != '='
					|| ft_memcmp(environ[j], str[i], len - 1)))
			j++;
		if (environ[j])
			ft_del_one_environ_var(environ[j]);
		else
		{
			ft_putstr_fd("unsetenv: no environement variable named \"", 2);
			ft_putstr_fd(str[i], 2);
			ft_putchar_fd('\"', 2);
			ft_putchar('\n');
		}
		i++;
	}
}

/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 08:51:18 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/06 14:19:08 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/include/libft.h"
# include "minishell.h"

extern	char	**environ;

int ft_check_commas(char *str)
{
	int i;
	int	comma_presence;

	i = 0;
	comma_presence = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			comma_presence++;
		i++;
	}
	if (comma_presence % 2)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			comma_presence++;
		i++;
	}
	if (comma_presence % 2)
		return (2);
	return (0);
}

void	ft_recognize_processes(char *str)
{
	char	**arguments;

	arguments = NULL;
	if (str)
	{
		arguments = ft_split_whitespaces_nokots(str);
		ft_launch_processes(arguments, environ);
	}
	(arguments) ? ft_tabdel(arguments) : 0;
}

int		ft_look_inside(char *line)
{
	int		comma_presence;
	comma_presence = 0;

	if (line)
	{
		comma_presence = ft_check_commas(line);
		line = find_aliases(line);
		(!comma_presence) ? ft_recognize_processes(line) : ft_complete_command(comma_presence, &line);
		return (1);
	}
	return (0);
}


int	main()
{
	char	*line;
	char	*line_cpy;

	line_cpy = NULL;
	line = NULL;
	ft_print_current_directory();
	environ = ft_tabdup(environ, ft_tabsize(environ));
	ft_file_to_string();
}
