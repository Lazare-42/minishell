/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 15:43:35 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 16:55:45 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *g_commands[9] = {"echo", "cd", "setenv", "unsetenv", "env",
	"exit", "chdir", "alias"};

int		ft_recognize_builtin_command(char *str)
{
	int		i;

	i = 0;
	while (g_commands[i])
	{
		if (ft_strcmp((char*)g_commands[i], str) == 0)
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
/*   Created: 2017/12/20 13:04:02 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/21 21:25:45 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"

static char		**ft_add_command_to_path(char **possible_path, char *arg)
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

char			**ft_find_prog_path(char *arg, char **environ)
{
	int			i;
	char		*tmp;
	char		**possible_program_path;

	i = 0;
	possible_program_path = NULL;
	while (environ[i] && environ && ft_memcmp(environ[i], "PATH=", 5) != 0)
		i++;
	if (!(environ[i]))
		return (NULL);
	tmp = &environ[i][5];
	possible_program_path = ft_strsplit(tmp, ':');
	return (ft_add_command_to_path(possible_program_path, arg));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advance_string_for_quote.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 10:23:02 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/20 10:23:03 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/*   Updated: 2017/12/29 14:55:13 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"
#include <unistd.h>

void	ft_call_to_chdir(char *str)
{
	char			path[1025];
	char			*tmp;
	extern	char	**environ;

	tmp = NULL;
	if (!(getcwd(path, 1025)) || (!(tmp = ft_strjoin("OLDPWD=", path))))
		return ;
	if (chdir(str))
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_memdel((void**)&tmp);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		if (!(environ = ft_tab_replacestr(&environ, &tmp, "OLDPWD=\0")))
			return ;
		if (!(getcwd(path, 1025)) || (!(tmp = ft_strjoin("PWD=", path))))
			return ;
		if (!(environ = ft_tab_replacestr(&environ, &tmp, "PWD=\0")))
			return ;
	}
}

void	ft_go_to_home(void)
{
	extern char **environ;
	int			i;

	i = 0;
	while (environ[i] && ft_memcmp(environ[i], "HOME=", 5))
		i++;
	if (environ[i])
	{
		if (chdir(&environ[i][5]))
			ft_putstr_fd("HOME variable set at a wrong value\n", 2);
	}
	else
		ft_putstr_fd("Inexistant Home variable\n", 2);
	return ;
}

void	ft_change_dir(char *str)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (!str || (str[0] == '~' && !(str[1])))
	{
		ft_go_to_home();
		return ;
	}
	if (environ && (str[0] == '-' && !str[1]))
	{
		while (environ && environ[i] && ft_memcmp(environ[i], "OLDPWD", 6))
			i++;
		if (environ[i])
			ft_call_to_chdir(&environ[i][7]);
		else
			ft_putstr_fd("OLDPWD not set\n", 2);
		return ;
	}
	ft_call_to_chdir(str);
	return ;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input_for_ctrl_keys.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 06:19:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 14:07:24 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

static	t_arg	*g_to_find = NULL;

static void	ft_check_key_up(t_arg *first, t_arg *new)
{
	if (first)
	{
		(g_to_find) ? ft_replace_content(new, 0) : 0;
		ft_advance_lst_to(first, new, &g_to_find, 1);
		(g_to_find) ? ft_replace_content(g_to_find, 1) : 0;
	}
}

static void	ft_check_key_down(t_arg *first, t_arg *new)
{
	if (first && g_to_find)
	{
		(g_to_find) ? ft_replace_content(new, 0) : 0;
		ft_advance_lst_to(first, new, &g_to_find, 0);
		(g_to_find) ? ft_replace_content(g_to_find, 1) : 0;
	}
}

int	ft_check_special_input(t_arg **new, int buf, t_arg **first_arg)
{
	if ((*new)->arg && *(*new)->arg && buf == 127)
	{
		ft_replace_content(*new, 0);
		(*new)->arg[ft_strlen((*new)->arg) - 1] = '\0';
		ft_replace_content(*new, 1);
	}
	if (!(*new)->arg && buf == '\n')
		ft_putchar('\n');
	if ((*new)->arg && buf == '\n')
	{
		g_to_find = NULL;
		((*new)->old_line) ? ft_memdel((void**)&(*new)->old_line) : NULL;
		(*new)->arg = ((*new)->line_right) ? ft_strjoinfree(&(*new)->arg, &(*new)->line_right, 'B') : (*new)->arg;
		(*((*new)->arg)) ? *first_arg = ft_store_args(*first_arg, *new) : 0;
		ft_putchar('\n');
		(*(*new)->arg) ? ft_look_inside((*new)->arg, first_arg) : 0;
		ft_replace_content(NULL, 0);
		(*new) = new_arg();
	}
	if (buf == 127 || buf == '\n')
		return (0);
	return (ft_check_input_for_ctrl_keys(new, buf, *first_arg));
}

static void	ft_check_key_left(t_arg **new)
{
	int len;

	if ((*new) && (*new)->arg)
	{
		len = ft_strlen((*new)->arg) - 1;
		if ((*new)->line_right && (*new)->line_right[0])
			(*new)->line_right = ft_strjoinfree_char_str((*new)->arg[len], &(*new)->line_right);
		else
			(*new)->line_right = ft_strdup(&(*new)->arg[len]);
		(*new)->arg[len] = '\0';
	}
}

static void	ft_check_key_right(t_arg **new)
{
	if (*new && (*new)->line_right && (*new)->line_right[0])
	{
		(*new)->arg = ft_strjoinfree_str_char(&(*new)->arg, (*new)->line_right[0]);
		(*new)->line_right = ft_strdupfrom_free((const char**)&((*new)->line_right), 1); 
	}
}

int			ft_check_input_for_ctrl_keys(t_arg **new, int buf, t_arg *first)
{
	t_arg	*tmp;

	tmp = NULL;
	if (buf == KEY_UP)
		ft_check_key_up(first, *new);
	if (buf == KEY_DOWN)
		ft_check_key_down(first, *new);
	if (buf == KEY_LEFT && *(*new)->arg)
		ft_check_key_left(new);
	if (buf == KEY_RIGHT)
		ft_check_key_right(new);
	if (buf == KEY_UP || buf == KEY_DOWN || buf == KEY_LEFT || buf == KEY_RIGHT)
		return (0);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:32:05 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 13:27:57 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_standby(void)
{
	ft_putchar('\r');
	ft_putstr("dquote> ");
}

char	*ft_del_one(char *command_line, int write_from)
{
	if (*command_line && &command_line[write_from])
	{
		(command_line)[ft_strlen(command_line) - 1] = ' ';
		ft_standby();
		ft_putstr(&command_line[write_from]);
		(command_line)[ft_strlen(command_line) - 1] = '\0';
		ft_standby();
		ft_putstr(&command_line[write_from]);
	}
	return (command_line);
}

char	*ft_join_print(char *command_line, int buf, int write_from)
{
	if (!(command_line = ft_strjoinfree_str_char(&command_line, buf)))
		return (NULL);
	ft_standby();
	ft_putstr(&command_line[write_from]);
	return (command_line);
}

void	ft_complete_command(int quote_type, char **command_line, t_arg **first)
{
	int		comma_presence;
	int		ret;
	long	buf;
	int		write_from;

	ft_putstr("dquote> ");
	ret = 1;
	write_from = ft_strlen(*command_line) - 1;
	while (ret == 1 && command_line)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (buf == 127 && command_line[0])
			*command_line = ft_del_one(*command_line, write_from);
		else if (buf == '\n')
			break ;
		else if (buf != 127 && buf != KEY_UP && buf
				!= KEY_DOWN && buf != KEY_LEFT && buf != KEY_RIGHT)
			*command_line = ft_join_print(*command_line, buf, write_from);
	}
	comma_presence = ft_check_commas(*command_line);
	ft_putchar('\n');
	(comma_presence != quote_type) ? ft_recognize_processes(*command_line, first) :
		ft_complete_command(quote_type, command_line, first);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 20:58:05 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 20:59:21 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_corresponding_variable(char *str)
{
	size_t		i;
	int			j;
	char extern **environ;

	i = ft_strlen(str);
	j = 0;
	str++;
	if (str)
	{
		while (environ[j] && (ft_memcmp(environ[j], str, i - 1)
					|| environ[j][i - 1] != '='))
			j++;
		if (environ[j])
			ft_putstr(&environ[j][i]);
	}
}

void	ft_parse(char **str)
{
	int		i;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 18:38:34 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 13:30:50 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_launch_forkk(t_arg **first, char **args)
{
	ft_launch_processes(args, first);
}

static void		ft_env_options(char **args, t_arg **first)
{
	int				i;
	int				j;
	char			**new_environ;
	extern	char	**environ;

	i = -1;
	j = -1;
	new_environ = ft_tabdup(environ, ft_tabsize(environ));
	while (args[++i] && args[i][0] && args[i][0] == '-')
	{
		if (args[i][0] && args[i][0] == '-' && (!args[i][1]))
			new_environ = NULL;
		while (args[i][++j])
		{
			if (args[i][j] == 'i')
				new_environ = NULL;
		}
	}
	while (args[i] && ft_strchr(args[i], '='))
	{
		new_environ = ft_setenv(&args[i], ft_new_environ_size(&args[i],
					new_environ), new_environ);
		i++;
	}
	(args[i]) ? ft_launch_forkk(first, &args[i]) : 0;
}

void			ft_env(char **args, t_arg **first)
{
	if (!(args[0]))
		return (ft_put_env());
	ft_env_options(args, first);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_processes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 20:59:40 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 14:29:44 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

void	ft_ex_myprog_or_exit(char **arguments,
		char **environ)
{
	if (execve(arguments[0], arguments, environ) == -1)
		ft_put_command_errors(arguments[0]);
}

static void	ft_launch_ext_command(char **arguments)
{
	int				i;
	char			**possible_path;
	int				forkk;
	extern char		**environ;

	i = 0;
	forkk = 1;
	possible_path = NULL;
	if (!(forkk = fork()))
	{
		if (environ[0])
			possible_path = ft_find_prog_path(arguments[0], environ);
		if (!possible_path && environ[0])
			ft_put_command_errors(arguments[0]);
		while (possible_path && possible_path[i] && execve(possible_path[i],
					arguments, environ) == -1)
			i++;
		if (!(possible_path))
			execve(arguments[0], arguments, NULL); 
		if (possible_path && !possible_path[i])
			ft_ex_myprog_or_exit(arguments, environ);
		exit(0);
	}
	if (forkk)
		wait(&forkk);
	(possible_path) ? ft_tabdel(possible_path) : 0;
}

static void	ft_launch_builtin_processes(int command_number, char **arguments, t_arg **first)
{
	if (arguments[1])
	{
		(command_number == 0) ? ft_echo(&arguments[1]) : 0;
		(command_number == 6) ? ft_change_dir(arguments[1]) : 0;
		(command_number == 7) ? ft_new_alias(&arguments[1]) : 0;
	}
	(command_number == 1) ? ft_change_dir(arguments[1]) : 0;
	(command_number == 2) ? ft_sort_setenv(&arguments[1]) : 0;
	(command_number == 3) ? ft_unsetenv(&arguments[1]) : 0;
	(command_number == 4) ? ft_env(&arguments[1], first) : 0;
	(command_number == 5) ? ft_putstr("exit\n") : 0;
	(command_number == 5) ? ft_listdel(first) : 0;
	(command_number == 5) ? exit(1) : 0;
}

void		ft_launch_processes(char **arguments, t_arg **first)
{
	int	command_number;

	command_number = -1;
	if (arguments[0])
	{
		if ((command_number = ft_recognize_builtin_command(arguments[0])) != -1)
			ft_launch_builtin_processes(command_number, arguments, first);
		else
			(ft_launch_ext_command(arguments));
	}
	ft_replace_content(NULL, 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_location_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:22:58 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/27 16:25:40 by lazrossi         ###   ########.fr       */
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

static int g_print_size;

static	char	*get_last_part(char *tmp)
{
	int		i;

	i = 0;
	if (tmp)
		i = ft_strlen(tmp);
	if (i > 1)
		i--;
	while (i && tmp[i] != '/')
		i--;
	if (i > 1)
		i++;
	return (&tmp[i]);
}

char			*ft_sort_git_name(DIR *dir, char *buf)
{
	char			*path;
	struct dirent	*dent;
	int				fd;
	int				ret;

	fd = -1;
	while (dir && (dent = readdir(dir)))
	{
		if (ft_memcmp(dent->d_name, "HEAD", 4) == 0)
		{
			path = ft_strjoin(getcwd(dent->d_name, 1024), "/.git/HEAD");
			fd = open(path, O_RDONLY);
			ret = read(fd, buf, 1024);
			(ret != -1) ? buf[ret - 1] = '\0' : 0;
			buf = get_last_part(buf);
			(path) ? ft_strdel(&path) : 0;
			close(fd);
		}
	}
	return (buf);
}

static char		*ft_get_git(void)
{
	DIR				*dir;
	char			*buf;
	char			*tmp;

	tmp = NULL;
	buf = NULL;
	if ((dir = opendir(".git")))
	{
		if (!(buf = ft_strnew(1025)))
			return (NULL);
		tmp = buf;
		buf = ft_sort_git_name(dir, buf);
		buf = ft_strdup(buf);
		ft_memdel((void**)&tmp);
		closedir(dir);
	}
	return (buf);
}

static int		set_pwd_var(void)
{
	extern char **environ;
	char		*path;

	if (!(path = ft_strnew(1024)))
		return (0);
	if (!(path = getcwd(path, 1025)))
	{
		ft_memdel((void**)&path);
		path = ft_strdup("! getcwd() failed, unknown shell location !\n");
	}
	if (!(path = ft_strjoinfree_one(&path, "PWD=", 'B')))
		return (0);
	if (!(environ = ft_tabdup_add_free(&environ, &path, 'B')))
	{
		ft_memdel((void**)&path);
		return (0);
	}
	ft_memdel((void**)&path);
	return (1);
}

void			ft_get_location_info(char **path, char **git)
{
	int		i;
	extern	char **environ;

	i = 0;
	g_print_size = 0;
	while (environ && environ[i] && ft_memcmp(environ[i], "PWD", 3))
		i++;
	if (environ && environ[i])
		*path = &environ[i][4];
	else
	{
		if ((set_pwd_var()))
			ft_get_location_info(path, git);
		else
			return ;
	}
	*path = get_last_part(*path);
	*git = ft_get_git();
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 07:21:24 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 16:06:58 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

static int	ft_define_cmp_size(t_arg *tmp, t_arg *new)
{
	int cmp_size;

	cmp_size = 0;
	if (tmp && (new)->old_line)
		cmp_size = ft_strlen((new)->old_line);
	else if (tmp && (new)->arg)
		cmp_size = ft_strlen((new)->arg);
	return (cmp_size);
}

static char	*ft_define_cmp(t_arg *tmp, t_arg *new)
{
	char *cmp;

	cmp = NULL;
	if (tmp && (new)->old_line)
		cmp = (new)->old_line;
	else if (tmp && (new)->arg)
		cmp = (new)->arg;
	return (cmp);
}

void	ft_advance_lst_to(t_arg *first, t_arg *new, t_arg **to_find, int forwrd)
{
	t_arg	*tmp;
	int		cmp_size;
	char	*cmp;
	int		previous_size;

	previous_size = (*to_find) ? ft_strlen((*to_find)->arg) : -1;
	tmp = (*to_find && forwrd) ? (*to_find)->next : first;
	tmp = (*to_find && !forwrd) ? (*to_find)->previous : tmp;
	cmp = ft_define_cmp(tmp, new);
	cmp_size = ft_define_cmp_size(tmp, new);
	while (tmp && forwrd && tmp->next && (ft_memcmp(cmp, tmp->arg, cmp_size)
				|| (int)ft_strlen(tmp->arg) == previous_size))
		tmp = tmp->next;
	while (tmp && !forwrd && (ft_memcmp(cmp, tmp->arg, cmp_size)
				|| (int)ft_strlen(tmp->arg) == previous_size))
		tmp = tmp->previous;
	if (tmp && tmp->arg && (!(ft_memcmp(cmp, tmp->arg, cmp_size))))
	{
		if (!((new)->old_line))
			(new)->old_line = (new)->arg;
		(new)->arg = tmp->arg;
		*to_find = tmp;
	}
}

void	ft_listdel(t_arg **first)
{
	t_arg	*tmp;

	tmp = NULL;
	while (first && *first)
		*first = (*first)->next;
	while (first && *first)
	{
		tmp = *first;
		*first = (*first)->previous;
		ft_memdel((void**)&(tmp->arg));
		ft_memdel((void**)&(tmp));
	}
}

t_arg	*new_arg(void)
{
	t_arg	*new;

	new = NULL;
	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	new->arg = NULL;
	new->old_line = NULL;
	new->line_right = NULL;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:47:06 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/20 13:00:45 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

void	ft_delete(char **alias_name, char **alias_value)
{
	if (*alias_name)
		ft_memdel((void**)alias_name);
	if (*alias_value)
		ft_memdel((void**)alias_value);
}

void	ft_add_alias(char **alias_name, char **alias_value, char **new_values)
{
	if (!(*alias_name = ft_strjoinfree_str_char(alias_name, '_')))
		return ;
	if (!(*alias_name = ft_strjoinfree(alias_name, &(new_values[0]), 'L')))
		ft_delete(alias_name, alias_value);
	if (!(*alias_name = ft_strjoinfree_str_char(alias_name, '\n')))
		ft_delete(alias_name, alias_value);
	if (!(*alias_value = ft_strjoinfree_str_char(alias_value, ',')))
		ft_delete(alias_name, alias_value);
	if (!(*alias_value = ft_strjoinfree(alias_value, &(new_values[1]), 'L')))
		ft_delete(alias_name, alias_value);
	if (!(*alias_value = ft_strjoinfree_str_char(alias_value, '\n')))
		ft_delete(alias_name, alias_value);
}

void	ft_creat_alias(char **alias_name, char **alias_value, char **new_values)
{
	if (!(*alias_name = ft_strjoin(new_values[0], "\n")))
		return ;
	if (!(*alias_value = ft_strjoin(new_values[1], "\n")))
		ft_delete(alias_name, alias_value);
}

void	ft_new_alias(char **new_values)
{
	int		fd;
	char	*alias_name;
	char	*alias_value;

	fd = -1;
	alias_value = NULL;
	alias_name = NULL;
	if (!(ft_put_alias_errors(new_values)))
		return ;
	if (!(fd = open("/Users/lazrossi/Documents/42/minishell/srcs/alias.txt",
					O_RDWR | O_CREAT, 0777)))
		return ;
	get_next_line(fd, &alias_name, '\n');
	get_next_line(fd, &alias_value, '\n');
	close(fd);
	if (alias_name && alias_value)
		ft_add_alias(&alias_name, &alias_value, new_values);
	else
		ft_creat_alias(&alias_name, &alias_value, new_values);
	fd = open("/Users/lazrossi/Documents/42/minishell/srcs/alias.txt", O_RDWR);
	write(fd, alias_name, ft_strlen(alias_name));
	write(fd, alias_value, ft_strlen(alias_value));
	ft_delete(&alias_name, &alias_value);
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
/*   Updated: 2017/12/20 15:58:53 by lazrossi         ###   ########.fr       */
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
			ft_putstr(". \nIf this appears to be an error, you might want to ");
			ft_putstr("check if your new alias includes a pre-existing one.\n");
		}
		if (underscore_nbr)
		{
			ft_putstr("Underscores separate aliases in alias.txt ");
			ft_putstr("Please remove any underscore of the alias\n");
		}
		return (0);
	}
		ft_putstr("WTF");
	return (1);
}

int		ft_put_alias_errors(char **str)
{
	int i;
	int j;
	int	underscore_nbr;

	ft_putabs(str, '\n');
	i = 0;
	underscore_nbr = 0;
	j = -1;
	while (str && *str && str[i])
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
/*   Created: 2017/12/18 05:26:19 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 15:33:51 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/include/libft.h"
#include <sys/ioctl.h>

static int	ft_compare_string_to_win(char *path, char *git, t_arg *line_info)
{
	struct	winsize window;
	int		arg_len;


	arg_len = 0;
	arg_len = ft_strlen(path) + ft_strlen(git)
		+ ft_strlen(line_info->arg) + ft_strlen(line_info->line_right);
	//	old_arg_len = ft_strlen(path) + ft_strlen(git)
	//		+ ft_strlen(erase) + ft_strlen(line_right);
	arg_len += (git) ? 9 : 5;
	//	old_arg_len += (git) ? 9 : 5;
	ioctl(1, TIOCGWINSZ, &window);
	if (arg_len == window.ws_col)
		//	&& old_arg_len > window.ws_col)
	{
		ft_putchar('\r');
		return (0);
	}
	else if (arg_len > window.ws_col)
		return (arg_len);
	else
		return (0);
}

static void ft_print_after_break(t_arg *line_info, int arg_len)
{
	int		window_size;
	int		path_len;
	int		new_cont_len;
	int		to_print_from;
	struct	winsize window;


	ioctl(1, TIOCGWINSZ, &window);
	window_size = window.ws_col;
	new_cont_len = ft_strlen(line_info->arg) + ft_strlen(line_info->line_right);
	path_len = (arg_len - new_cont_len);
	ft_putstr(" ");
	ft_putchar('\r');
	to_print_from = window_size - path_len;
	while ((int)ft_strlen(&(line_info->arg[to_print_from])) > window_size)
		to_print_from += window_size;
	ft_putstr(&(line_info->arg[to_print_from]));
}

static void ft_print_current_directory(char *path, char *git)
{
	if (path)
	{
		ft_putstr("\e[0;91m");
		ft_putchar('\r');
		ft_putchar('/');
		ft_putstr(path);
		if (git)
		{
			ft_putstr("\e[0m");
			ft_putstr("\e[0;90m");
			git ? ft_putstr("[git@]") : 0;
			git ? ft_putstr(git) : 0;
		}
	}
	ft_putstr("\\ ");
	ft_putstr("\e[0m");
}

void	ft_replace_content(t_arg *line_info, int put)
{
	char	*path;
	char	*git;
	int		location_len;

	path = NULL;
	git = NULL;
	ft_get_location_info(&path, &git);
	if (line_info && (location_len = ft_compare_string_to_win(path, git, line_info)))
	{
		ft_print_after_break(line_info, location_len);
		return ;
	}
	ft_print_current_directory(path, git);
	if (line_info)
	{
		(line_info->old_line) ? ft_putwhites(ft_strlen(line_info->arg) + ft_strlen(line_info->line_right)) : 0;
		(line_info->old_line) ? ft_print_current_directory(path, git) : 0;
		(line_info->arg && put) ? ft_putstr(line_info->arg) : 0;
		(line_info->line_right && put) ? ft_putstr(line_info->line_right) : 0;
		(line_info->line_right && put) ? ft_print_current_directory(path, git) : 0;
		(line_info->line_right && put) ? ft_putstr(line_info->arg): 0;
	}
	if (git)
		ft_memdel((void**)&git);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 06:38:27 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 15:00:06 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_put_env(void)
{
	extern char **environ;

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
/*   Updated: 2017/12/28 15:33:48 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

static int	set_non_canonical_input(void)
{
	struct termios termios_cpy;

	if (tcgetattr(0, &termios_cpy) != 0)
		return (0);
	termios_cpy.c_cc[VMIN] = 1;
	termios_cpy.c_cc[VTIME] = 0;
	termios_cpy.c_lflag &= (IGNBRK);
	termios_cpy.c_lflag &= (ICANON);
	if (tcsetattr(0, TCSANOW, &termios_cpy) != 0)
		return (0);
	return (1);
}

void	ft_replace_old_line(t_arg *new)
{
	if (new->old_line)
		ft_memdel((void**)&new->old_line);
	new->old_line = ft_strdup(new->arg);
}


void		ft_file_to_string(void)
{
	long	buf;
	int		ret;
	t_arg	*first;
	t_arg	*new;
	t_arg	*to_find;

	ret = 1;
	first = NULL;
	new = NULL;
	to_find = NULL;
	if (!(set_non_canonical_input()) || (!(first = ft_store_args(first, NULL))))
		return ; 
	if (!(new = new_arg()))
		return ;
	while (ret && new)
	{
		buf = 0;
		ret = read(0, &buf, sizeof(long));
		if (new && ft_check_special_input(&new, buf, &first))
			if (!(new->arg = ft_strjoinfree_str_char(&((new)->arg), buf)))
				return ;
		ft_replace_content(new, 1);
		if (new && buf != KEY_UP && buf != KEY_DOWN && new->arg)
			ft_replace_old_line(new);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:59:50 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 15:09:03 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_pathlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
		return (i);
	else
		return (0);
}

static char		*ft_add_env_var(char *env_location, char *new_env)
{
	if (env_location)
		ft_strdel(&env_location);
	env_location = ft_strdup(new_env);
	return (env_location);
}

int				ft_new_environ_size(char **args, char **environ_tocpy)
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

char			**ft_setenv(char **args, int new_environ_size,
		char **environ_tocpy)
{
	int			i;
	int			j;
	size_t		var_len;
	char		**new_env;
	extern char	**environ;

	i = -1;
	var_len = 0;
	new_env = ft_tabdup(environ_tocpy, new_environ_size);
	(environ_tocpy) ? ft_tabdel(environ_tocpy) : 0;
	while (args[++i])
	{
		j = 0;
		var_len = ft_pathlen(args[i]);
		while (var_len && new_env[j] &&
		(((ft_pathlen(new_env[j]) < var_len
			|| new_env[j][var_len] != '='
			|| ft_memcmp(args[i], new_env[j], var_len)))
	|| (new_env[j] && var_len >= ft_strlen(new_env[j]))))
			j++;
		if (var_len)
			new_env[j] = ft_add_env_var(new_env[j], args[i]);
	}
	return (new_env);
}

void			ft_sort_setenv(char **args)
{
	int			i;
	extern char	**environ;

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:53:48 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 15:35:13 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>

static	void	ft_place_element_in_tern_tree(t_arg **first, t_arg *new)
{
	new->next = *first;
	(*first)->previous = new;
	*first = new;
}

static	t_arg	*ft_store_command_historic(t_arg *first)
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
		ft_replace_content(NULL, 0);
		return (new_arg());
	}
	else
		while ((new = new_arg()) && get_next_line(fd, &new->arg, '\n'))
		{
			if (first)
				ft_place_element_in_tern_tree(&first, new);
			else
				first = new;
		}
	if (new)
		ft_memdel((void**)&new);
	close(fd);
	ft_replace_content(NULL, 0);
	return (first);
}

t_arg			*ft_store_args(t_arg *first, t_arg *new_arg)
{
	int		fd;

	fd = -1;
	if (!first)
		return (ft_store_command_historic(first));
	fd = open("/Users/lazrossi/Documents/42/minishell/historic.txt", O_WRONLY);
	if (fd != -1)
	{
		lseek(fd, 0, SEEK_END);
		write(fd, new_arg->arg, ft_strlen(new_arg->arg));
		write(fd, "\n", 1);
	}
	ft_place_element_in_tern_tree(&first, new_arg);
	close(fd);
	return (first);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:51:33 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/18 21:53:32 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_del_one_environ_var(char *str)
{
	int			i;
	int			to_del;
	extern char **environ;

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

void			ft_unsetenv(char **str)
{
	int			i;
	int			j;
	int			len;
	extern char **environ;

	i = 0;
	len = 0;
	while (str[i])
	{
		len = ft_strlen(str[i]);
		j = 0;
		while (environ[j] && (environ[j][len] != '='
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:50:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/29 14:32:11 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "minishell.h"

int		ft_check_commas(char *str)
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

void	ft_recognize_processes(char *str, t_arg **first)
{
	char			**arguments;

	arguments = NULL;
	if (str)
	{
		if (!(arguments = ft_split_whitespaces_nokots(str)))
			return ;
		ft_launch_processes(arguments, first);
	}
	(arguments) ? ft_tabdel(arguments) : 0;
}

int		ft_look_inside(char *line, t_arg **first)
{
	int		comma_presence;

	comma_presence = 0;
	if (line)
	{
		comma_presence = ft_check_commas(line);
		(!comma_presence) ? ft_recognize_processes(line, first)
			: ft_complete_command(comma_presence, &line, first);
		return (1);
	}
	return (0);
}

int		main(void)
{
	extern char **environ;

	if (!(environ = ft_tabdup(environ, ft_tabsize(environ))))
		return (0);
	ft_file_to_string();
}
