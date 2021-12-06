SERVER = server
CLIENT = client
HEADER_FILES = minitalk.h
SERVER_SRCS = source/server.c
CLIENT_SRCS = source/client.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
LIBFT = libft/libft.a
CC = gcc
C_FLAGS = -Wall -Wextra -Werror -I.

all: $(SERVER) $(CLIENT)

%.o: %.c $(HEADER_FILES)
	$(CC) $(C_FLAGS) -c $< -o $@

$(SERVER): $(SERVER_OBJS) $(LIBFT)
	$(CC) $(SERVER_OBJS) $(LIBFT) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CLIENT_OBJS) $(LIBFT) -o $(CLIENT)

$(LIBFT):
	make -C libft

norme:
	make -C libft norme
	@norminette $(SERVER_SRCS)
	@norminette $(CLIENT_SRCS)
	@norminette $(HEADER_FILES)

clean:
	make -C libft clean
	rm -f $(OBJ_FILES)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all norme clean fclean re
