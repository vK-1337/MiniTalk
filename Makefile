# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 14:40:36 by vda-conc          #+#    #+#              #
#    Updated: 2023/12/09 16:49:36 by vda-conc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_1 = client.c
OBJ_1 = $(SRC_1:.c=.o)

SRC_2 = server.c
OBJ_2 = $(SRC_2:.c=.o)

SRC_3 = server_bonus.c
OBJ_3 = $(SRC_3:.c=.o)

SRC_4 = client_bonus.c
OBJ_4 = $(SRC_4:.c=.o)

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -L./libft -lft

NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus
GREEN = \033[0;32m
NC = \033[0m
YELLOW = \e[0;93m

../libft/libft.a: FORCE
	@$(MAKE) -C ./libft

$(NAME_CLIENT): $(OBJ_1) ../libft/libft.a
	$(CC) $(OBJ_1) $(CFLAGS) $(LDFLAGS) -o $(NAME_CLIENT)
	@echo "	 			+---------------------+\n\
					|  $(YELLOW)    CLIENT $(GREEN)[OK]$(NC)    |\n\
					+---------------------+"

$(NAME_SERVER): $(OBJ_2) ../libft/libft.a
	$(CC) $(CFLAGS) $(OBJ_2) $(LDFLAGS) -o $(NAME_SERVER)
	@echo "	 			+---------------------+\n\
					|  $(YELLOW)   SERVER $(GREEN)[OK]$(NC)     |\n\
					+---------------------+"
$(NAME_SERVER_BONUS): $(OBJ_3) ../libft/libft.a
		$(CC) $(OBJ_3) $(CFLAGS) $(LDFLAGS) -o $(NAME_SERVER_BONUS)
		@echo "	 			+---------------------+\n\
					|  $(YELLOW)BONUS SERVER $(GREEN)[OK]$(NC)  |\n\
					+---------------------+"
$(NAME_CLIENT_BONUS): $(OBJ_4) ../libft/libft.a
		$(CC) $(OBJ_4) $(CFLAGS) $(LDFLAGS) -o $(NAME_CLIENT_BONUS)
		@echo "	 			+---------------------+\n\
					|  $(YELLOW)BONUS CLIENT $(GREEN)[OK]$(NC)  |\n\
					+---------------------+"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

m: $(NAME_CLIENT) $(NAME_SERVER)

b: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

clean:
	rm -f $(OBJ_1) $(OBJ_2) $(OBJ_3) $(OBJ_4)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re FORCE
