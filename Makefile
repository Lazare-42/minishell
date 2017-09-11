NAME = minishell

SOURCES = ./builtin_commands.c \
./find_path.c \
./ft_change_dir.c \
./ft_echo.c \
./ft_file_to_string.c \
./ft_print_errors.c \
./ft_print_info.c \
./ft_put_env.c \
./ft_set_env.c \
./main.c 

LIBDIR = libft
SDIR = srcs
ODIR = bin
CFLAGS = -Wall -Wextra -Werror
CDEBUG = -fno-omit-frame-pointer -fsanitize=address -g
INCDIR = includes
LDFLAGS = -L$(LIBDIR) -lft
LNCURSES = -lncurses
CC = clang
SRCS = $(addprefix $(SDIR)/, $(SOURCES:.c=.c))
OBJS = $(addprefix $(ODIR)/, $(SOURCES:.c=.o))
OK = echo "[32m OK ✓ [0m"

all: lib mkbin $(NAME)

lib:
	@echo "Compiling libft ..."
	@-make -C $(LIBDIR)
	@$(OK)

mkbin:
	@mkdir -p $(ODIR)


$(NAME): $(OBJS)
	@echo "Compiling minishell ..."
	@-$(CC) $(CFLAGS) $(CDEBUG) -o $(NAME) $(OBJS) -I$(INCDIR) $(LDFLAGS) $(LNCURSES)
	@$(OK)

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) $(CDEBUG) -c -o $@ $< -I$(INCDIR)

clean:
	@/bin/rm -rf $(ODIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all
