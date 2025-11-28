# === Variables ===
CFLAGS  = -Wall -Wextra -Werror -g 

LDFLAGS = -lreadline

NAME    = minishell

SRCS    = main.c \
          minishell.c \
          sources_FE/cmd_lst_utils.c \
          sources_FE/fe_launcher.c \
          sources_FE/lexer.c \
          sources_FE/lexer_utils.c \
          sources_FE/parser.c \
          sources_FE/parser_utils.c \
          sources_FE/redir_lst_utils.c \
          sources_FE/redirs_utils.c \
          sources_FE/syntax_error.c \
          sources_FE/token_lst_utils.c \
          sources_FE/tokenizer.c

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