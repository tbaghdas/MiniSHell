# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 18:46:27 by tbaghdas          #+#    #+#              #
#    Updated: 2025/12/11 00:18:11 by tbaghdas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES	= ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
		ft_strlcat.c ft_strcmp.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
		ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
		ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c  ft_striteri.c\
		ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
		ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c \
		ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_strjoin_null.c
		
OFILES	= $(CFILES:.c=.o)

BONUS	= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstnew.c ft_lstsize.c
		
BONUS_OFILES	= $(BONUS:.c=.o)

NAME	= libft.a

CFLAGS	= -Wall -Wextra -Werror -g

%.o: %.c	$(libft.h) Makefile
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES) 

clean:
	rm -f $(OFILES) $(BONUS_OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:	$(OFILES) $(BONUS_OFILES)
		ar rcs $(NAME) $(OFILES) $(BONUS_OFILES)

.PHONY:  all clean fclean re bonus