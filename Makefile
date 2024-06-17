NAME = philo

C_FLAGS = -Wall -Wextra

SRC =	parce.c\
		libft_utils.c\
		philo.c\
		utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)
	

$(NAME) : $(OBJ)
	$(CC) $(C_FLAGS) $(OBJ) -o $(NAME) -fsanitize=thread

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
fclean:
	@rm  -f $(NAME) $(OBJ)

re:    fclean all