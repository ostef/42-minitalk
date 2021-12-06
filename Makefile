SERVER = server
CLIENT = client
HEADER_FILES = minitalk.h
SHARED_SRCS = 
SERVER_SRCS = source/server.c
CLIENT_SRCS = source/client.c
SHARED_OBJS = $(SHARED_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
LIBFT = libft/libft.a
CC = gcc
C_FLAGS = -Wall -Wextra -Werror -I.

all: $(SERVER) $(CLIENT)

$(SHARED_OBJS): %.o: %.c $(HEADER_FILES)
	$(CC) $(C_FLAGS) -c $< -o $@

$(SERVER_OBJS): %.o: %.c $(HEADER_FILES)
	$(CC) $(C_FLAGS) -c $< -o $@

$(CLIENT_OBJS): %.o: %.c $(HEADER_FILES)
	$(CC) $(C_FLAGS) -c $< -o $@

$(SERVER): $(SHARED_OBJS) $(SERVER_OBJS) $(LIBFT)
	$(CC) $(SHARED_OBJS) $(SERVER_OBJS) $(LIBFT) -o $(SERVER)

$(CLIENT): $(SHARED_OBJS) $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(SHARED_OBJS) $(CLIENT_OBJS) $(LIBFT) -o $(CLIENT)

$(LIBFT):
	make -C libft

norme:
	make -C libft norme
	@norminette $(SRC_FILES)
	@norminette $(HEADER_FILES)

clean:
	make -C libft clean
	rm -f $(OBJ_FILES)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all norme clean fclean re
