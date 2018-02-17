NAME = minishell

SOURCES = builtin_commands.c \
find_path.c \
ft_advance_string_for_quote.c \
ft_change_dir.c \
operate_special_input.c \
ft_complete_command.c \
ft_echo.c \
ft_env.c \
ft_launch_processes.c \
ft_location_info.c \
ft_lst_operations.c \
ft_print_errors.c \
termcaps.c \
ft_put_env.c \
ft_read_input.c \
ft_set_env.c \
ft_store.c \
ft_unsetenv.c \
main.c  \
ft_get_terminfo.c \
ft_check_commas.c \
get_cursor_position.c \
print_info2.c \

LIBDIR = libft
SDIR = srcs
ODIR = bin
CFLAGS = -Wall -Wextra -Werror
INCDIR = includes
LDFLAGS = -L$(LIBDIR) -lft
LNCURSES = -lncurses
CC = clang
SRCS = $(addprefix $(SDIR)/, $(SOURCES:.c=.c))
OBJS = $(addprefix $(ODIR)/, $(SOURCES:.c=.o))
OK = echo "[32m OK ✓ [0m"

all: lib mkbin $(NAME)

lib:
	@echo "Archiving libft ..."
	@-make -C $(LIBDIR)
	@$(OK)

mkbin:
	@mkdir -p $(ODIR)


$(NAME): $(OBJS)
	@ echo "[35m Compiling minishell...[0m"
	@-$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) -I$(INCDIR) $(LDFLAGS) $(LNCURSES)
	@$(OK)

$(ODIR)/%.o : $(SDIR)/%.c
	@ echo "[34m Assembling minishell object: [0m" $@
	@ $(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)

clean:
	@ echo "[31m Cleaning minishell... [0m"
	@/bin/rm -rf $(ODIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all
