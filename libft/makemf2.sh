#!/bin/sh
read -p "Are you sure to overwrite the makefile ?" -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]] ; then
	rm -f makefile
	echo "NAME = $1" > Makefile
	srcs=$(find srcs -name "*\.c" | sed "s/^srcs/\./g" | sed "s/$/ \\\/g" | sed '$s/\\//')
	echo >> Makefile
	echo "SOURCES = $srcs" >> Makefile
	echo >> Makefile
	echo "LIBDIR = libft" >> Makefile
	echo "SDIR = srcs" >> Makefile
	echo "ODIR = bin" >> Makefile
	echo "CFLAGS = -Wall -Wextra -Werror" >> Makefile
	echo "CDEBUG = -fno-omit-frame-pointer -fsanitize=address -g" >> Makefile
	echo "INCDIR = include" >> Makefile
	echo "LDFLAGS = -L\$(LIBDIR) -lft" >> Makefile
	echo "LNCURSES = -lncurses" >> Makefile
	echo "CC = clang" >> Makefile
	echo "SRCS = \$(addprefix \$(SDIR)/, \$(SOURCES:.c=.c))" >> Makefile
	echo "OBJS = \$(addprefix \$(ODIR)/, \$(SOURCES:.c=.o))" >> Makefile
	echo >> Makefile
	echo "all: lib mkbin \$(NAME)" >> Makefile
	echo >> Makefile
	echo "lib:" >> Makefile
	echo "	make -C \$(LIBDIR)" >> Makefile
	echo >> Makefile
	echo "mkbin:" >> Makefile
	echo "	@mkdir -p \$(ODIR)" >> Makefile
	dir=$(find srcs -type d | sed "s/^srcs//g" | sed '1d' | sed "s/^/\\\t@\/bin\/mkdir -p \$(ODIR)/g")
	echo "$dir" >> Makefile
	echo >> Makefile
	echo "\$(NAME): \$(OBJS)" >> Makefile
	echo "	\$(CC) \$(CFLAGS) \$(CDEBUG) -o \$(NAME) \$(OBJS) -I\$(INCDIR) \$(LDFLAGS) \$(LNCURSES)" >> Makefile
	echo >> Makefile
	echo "\$(ODIR)/%.o : \$(SDIR)/%.c" >> Makefile
	echo "	\$(CC) \$(CFLAGS) \$(CDEBUG) -c -o \$@ \$< -I\$(INCDIR)" >> Makefile
	echo >> Makefile
	echo "clean:" >> Makefile
	echo "	@/bin/rm -rf \$(ODIR)" >> Makefile
	echo "	@make -C \$(LIBDIR) clean" >> Makefile
	echo >> Makefile
	echo "fclean: clean" >> Makefile
	echo "	@/bin/rm -rf \$(NAME)" >> Makefile
	echo "	@make -C \$(LIBDIR) fclean" >> Makefile
	echo >> Makefile
	echo "re: fclean all" >> Makefile
fi
