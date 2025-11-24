# === Variables ===
CFLAGS  = -Wall -Wextra -Werror -g 

LDFLAGS = -lreadline

NAME    = minishell

SRCS    = sources_FE/lexer.c \
          sources_FE/lexer_utils.c \
          sources_FE/token_lst_utils.c \
          sources_FE/tokens.c

OBJS    = $(SRCS:.c=.o)

LIBFT_DIR  = libft
LIBFT = $(LIBFT_DIR)/libft.a

# === Rules ===
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

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