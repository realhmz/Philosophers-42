NAME = philo


C_FLAGS = -Wall -Wextra -Werror  -fsanitize=thread
SRC =	parce.c\
		libft_utils.c\
		philo.c\
		utils.c\
		routine.c

OBJ = $(SRC:.c=.o)

all : $(NAME)
	

$(NAME) : $(OBJ)
	 $(CC) $(C_FLAGS) $(OBJ) -o $(NAME)  

	

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
fclean:
	@rm  -f $(NAME) $(OBJ)

re:    fclean all
