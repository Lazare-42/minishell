
void	ft_replace_old_line(t_arg *new)
{
	if (new->old_line)
		ft_memdel((void**)&new->old_line);
	new->old_line = ft_strdup(new->arg);
}

int		ft_file_to_string(t_arg *first)
{
	char	buf[8];
	int		ret;
	t_arg	*new;
	t_arg	*to_find;

	ret = 1;
	new = NULL;
	to_find = NULL;
	first = NULL;
	if (!(new = new_arg()))
		return (put_fatal_error("could not malloc a new argument"));
	while (ret && new)
	{
		ret = read(0, &buf, 3);
		if (buf[0] != 27 && buf[0] != '\n' && buf[0] != 127)
		{
			ft_putchar(buf[0]);
			if (!(new->arg = ft_strjoinfree_str_char(&((new)->arg), buf[0])))
				return (put_fatal_error("could not malloc a char*"));
		}
		if (buf == K_UP)
			ft_putstr("haha");
		/*
		if (buf[0] == 27 || buf[0] == '\n' || buf[0] == 127)
			operate_special_input(&new, buf, &first);
		if (new && buf != KEY_UP && buf != KEY_DOWN && new->arg && *new->arg)
			ft_replace_old_line(new);
			*/
	}
	return (put_fatal_error("read or malloc error in ft_file_to_string()"));
}
