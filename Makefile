# === Variables ===
CFLAGS  = -Wall -Wextra -Werror -g

NAME    = minishell

SRCS    = lexer.c \
          lexer_utils.c \
          token_lst_utils.c \
          tokens.c

OBJS    = $(SRCS:.c=.o)

LIBFT_DIR  = libft
LIBFT = $(LIBFT_DIR)/libft.a

# === Rules ===
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re