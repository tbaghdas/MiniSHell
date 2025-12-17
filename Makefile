# === Variables ===
CFLAGS  = -Wall -Wextra -Werror -g

LDFLAGS = -lreadline -lhistory

NAME    = minishell

SRCS    = main.c \
		  minishell.c \
		  sources_FE/cmd_lst_utils.c \
		  sources_FE/expander.c \
		  sources_FE/expander_env.c \
		  sources_FE/expander_heredoc.c \
		  sources_FE/expander_utils.c \
		  sources_FE/freers.c \
		  sources_FE/heredoc.c \
		  sources_FE/lexer.c \
		  sources_FE/lexer_utils.c \
		  sources_FE/lex_par_exp.c \
		  sources_FE/parser.c \
		  sources_FE/parser_utils.c \
		  sources_FE/redir_lst_utils.c \
		  sources_FE/signal_utils.c \
		  sources_FE/syntax_error.c \
		  sources_FE/token_lst_utils.c \
		  sources_FE/tokenizer.c \
		  built_in/built_in1.c \
		  built_in/built_in2.c \
		  built_in/utils.c \
		  built_in/utils2.c \
		  built_in/utils3.c \
		  built_in/utils4.c \
		  built_in/utils5.c \
		  cmd_parsing/cmd_parsing1.c \
		  cmd_parsing/cmd_parsing2.c \
		  cmd_parsing/cmd_parsing3.c \
		  cmd_parsing/cmd_parsing4.c \
		  cmd_parsing/create_env.c \
		  signals/signals.c

OBJS    = $(SRCS:.c=.o)

LIBFT_DIR  = libft
LIBFT = $(LIBFT_DIR)/libft.a

# === Rules ===
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

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