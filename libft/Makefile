# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/27 14:56:05 by lazrossi          #+#    #+#              #
#    Updated: 2017/12/30 21:41:21 by lazrossi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_tabdel.c \
	  ft_freetables.c \
	  ft_int_size.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_itoa.c \
	  ft_lstadd.c \
	  ft_lstdel.c \
	  ft_lstdelone.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_lstnew.c \
	  ft_memalloc.c \
	  ft_memccpy.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memdel.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_printtables.c \
	  ft_putchar.c \
	  ft_putchar_fd.c \
	  ft_putendl.c \
	  ft_putendl_fd.c \
	  ft_putnbr.c \
	  ft_putnbr_fd.c \
	  ft_putstr.c \
	  ft_putstr_fd.c \
	  ft_split_whitespaces.c \
	  ft_strcat.c \
	  ft_strchr.c \
	  ft_strclr.c \
	  ft_strcmp.c \
	  ft_strcpy.c \
	  ft_strdel.c \
	  ft_strdup.c \
	  ft_strequ.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strjoin.c \
	  ft_strjoinfree.c \
	  ft_strlcat.c \
	  ft_strlen.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strncat.c \
	  ft_strncmp.c \
	  ft_strncpy.c \
	  ft_strnequ.c \
	  ft_strnew.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strsplit.c \
	  ft_strstr.c \
	  ft_strsub.c \
	  ft_strtrim.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ./ft_putabs.c \
	  ./ft_advance_for_quotes.c \
	  ./get_next_line.c  \
	  ./ft_split_whitespaces_nokots.c \
	  ./ft_str_isalpha.c \
	  ./ft_tabdup.c \
	  ./ft_tabsize.c \
	  ./ft_putwhites.c \
	  ./ft_tabdup_and_add.c \
	  ./ft_split_char.c \
	  ./ft_strjoinfree_str_char.c \
	  ./ft_strjoinfree_char_str.c \
	  ./ft_strdupfrom_free.c \
	  ./ft_tabdup_add_free.c \
	  ./ft_strjoinfree_one.c \
	  ./ft_tab_replacestr.c \
      ./ft_str_is_printable.c \
	  ./int_ft_putchar.c \
	  ./ft_debug.c \

OBJECT = $(SRC:.c=.o)

CLEAN = /bin/rm -f

CC = gcc -Wall -Wextra -Werror -c 

ARCH = ar rc

all: $(NAME)

$(NAME): $(OBJECT)
	@- $(CC) $(SRC)
	@- $(ARCH) $(NAME) $(OBJECT)

$(OBJECT): %.o: %.c

clean: 
	@-$(CLEAN) $(OBJECT)

fclean: clean
	@-$(CLEAN) $(NAME)

re: fclean all
