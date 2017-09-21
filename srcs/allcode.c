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
	char	*commands[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};
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
		if (chdir(str))
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putchar_fd('\n', 2);
		}
		else
			ft_setenv("PWD", str);
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
	new_line = ft_strjoinfree(&command_line, &new_line, 'B');
	(comma_presence == quote_type) ? ft_recognize_processes(new_line) :
		ft_complete_command(quote_type, new_line);
}
#include "../includes/minishell.h"

void	ft_echo(char **str, int quote_presence)
{
	quote_presence++;
	if (!(ft_memcmp(str[0], "-n", 2)))
		ft_putabs(&str[1], ' ');
	else
	{
		ft_putabs(str, ' ');
		ft_putchar('\n');
	}
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
#include "fcntl.h"
#include "unistd.h"

char	*ft_file_to_string()
{
	char	*buf;
	int		ret;
	int		fd;

	fd = 0;
	ret = 1;
	if (!(buf = ft_strnew(4096)))
		return (NULL);
	if ((ret = read(fd, buf, 4096)))
		return (buf);
	return (buf);
}
#include "../includes/minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>
# include <stdlib.h>

extern char		**environ;

static void	ft_launch_ext_command(char **arguments)
{
	int 	i;
	char 	**possible_path;
	char	*my_prog_path;
	int		forkk;

	i = 0;
	forkk = 1;
	possible_path = NULL;
	possible_path = ft_find_prog_path(arguments[0]);
	my_prog_path = NULL;
	forkk = fork();
	if (!(forkk))
	{
		while (possible_path[i] && execve(possible_path[i], arguments, environ) == -1)
			i++;
		if (!possible_path[i])
		{
			my_prog_path = ft_find_my_prog_path(arguments[0]);
			if (my_prog_path)
			{
				if (execve(my_prog_path, arguments, environ) == -1)
					ft_put_command_errors(arguments[0]);
			}
		}
		exit(0);
	}
	if (forkk)
		wait(&forkk);
	(possible_path) ? ft_tabdel(possible_path) : 0;
}

static void	ft_launch_builtin_processes(int command_number, char **arguments)
{
	(command_number == 0) ? ft_echo(&arguments[1], 0): 0;
	(command_number == 1) ? ft_change_dir(arguments[1]) : 0;
	(command_number == 2) ? ft_sort_setenv(&arguments[1]): 0;
	(command_number == 3) ? ft_putstr("unsetenv\n") : 0;
	(command_number == 4) ? ft_put_env(): 0;
	(command_number == 5) ? ft_putstr("exit\n") : 0;
	(command_number == 5) ? exit (1): 0;
}

void	ft_launch_processes(char **arguments)
{
	int 	command_number;

	if (arguments[0])
	{
		if ((command_number = ft_recognize_builtin_command(arguments[0])) != -1)
			ft_launch_builtin_processes(command_number, arguments);
		else (ft_launch_ext_command(arguments));
	}
	ft_print_current_directory();
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

	i = 0;
	if (tmp)
		i = ft_strlen(tmp);
	if (i > 1)
		i--;
	while (tmp[i] != '/')
		i--;
	if (i > 1)
		i++;
	return (&tmp[i]);
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
				ft_putstr(get_last_part(buf));
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
	if (tmp)
		ft_putstr(get_last_part(tmp));
	ft_putstr("\e[0m");
	ft_putstr("\e[0;90m");
	ft_print_git();
	ft_putchar(' ');
	ft_putstr("\e[0m");
}
#include "../includes/minishell.h"

extern char **environ;

void	ft_put_env()
{
	ft_putabs(environ, '\n');
}
#include "../includes/minishell.h"

extern char** environ;

void	ft_setenv(char *name, char *value)
{
	int		i;
	char	*tmp;
	int		nbr;
	int		name_len;

	i = 0;
	nbr = 0;
	name_len = ft_strlen(name);
	while (environ[i] && ft_memcmp(environ[i], name, name_len))
		i++;
	tmp = ft_strjoin(name, "=");
	if (!environ[i])
	{
		environ[i] = (value) ? ft_strjoinfree(&tmp, &value, 'L') : tmp;
		i++;
		environ[i] = NULL;
		return ;
	}
	environ[i] = (value) ? ft_strjoinfree(&tmp, &value, 'L') : tmp;
}

void	ft_sort_setenv(char	**args)
{
	if (!args[0])
	{
		(ft_putabs(environ, '\n'));
		return ;
	}
	if (args && args[0] && args[1] && args[2])
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	else if (args && args[0])
		ft_setenv(args[0], args[1]);
}
#include "minishell.h"
#include <stdlib.h> 

static void	ft_place_element(t_arg **tmp, t_arg *new)
{
	if (ft_strcmp((*tmp)->arg, new->arg) > 0)
	{
		if (!((*tmp)->left))
			(*tmp)->left = new;
		else
			ft_place_element(&((*tmp)->left), new);
	}
	if (ft_strcmp((*tmp)->arg, new->arg) < 0)
	{
		if (!((*tmp)->right))
			(*tmp)->right = new;
		else
			ft_place_element(&(*tmp)->right, new);
	}
	if (ft_strcmp((*tmp)->arg, new->arg) == 0)
	{
		if (!((*tmp)->middle))
			(*tmp)->middle = new;
		else
			ft_place_element(&(*tmp)->middle, new);
	}
	return ;
}

static t_arg	*new_arg(char *line)
{
	t_arg 	*new;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	new->arg = ft_strdup(line);
	new->left = NULL;
	new->middle = NULL;
	new->right = NULL;
	return (new);
}

t_arg	*ft_store_args(char	*line, t_arg *first)
{
	t_arg	*tmp;
	t_arg	*new;
	
	tmp = NULL;
	new = NULL;
	if (!first)
		return (new_arg(line));
	tmp = first;
	new = new_arg(line);
	if (new)
		ft_place_element(&tmp, new);
	return (first);
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
		arguments = ft_split_whitespaces(str);
		ft_strdel(&str);
		ft_launch_processes(arguments);
	}
	(arguments) ? ft_tabdel(arguments) : 0;
}

int	main()
{
	char	*line;
	char	*line_cpy;
	t_arg	*argument_list;
	int		comma_presence;

	argument_list = NULL;
	line_cpy = NULL;
	line = NULL;
	comma_presence = 0;
	ft_print_current_directory();
	while  ((line = ft_file_to_string()) || (!ft_strlen(line)))
	{
		if (ft_strchr(line, '\n'))
		{
			argument_list = ft_store_args(line, argument_list);
			comma_presence = ft_check_commas(line);
			(!comma_presence) ? ft_recognize_processes(line) : ft_complete_command(comma_presence, line);
		}
	}
}
