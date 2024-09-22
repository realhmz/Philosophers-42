NAME = philo


C_FLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
SRC =	parce.c\
		libft_utils.c\
		philo.c\
		utils.c\
		routine.c\
		more_utils.c\
		eat.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)
	

$(NAME) : $(OBJ)
	 $(CC) $(C_FLAGS) $(OBJ) -o $(NAME)  

	

.c.o :
	$(CC) -Wall -Wextra -Werror -c $< -o $@

clean:
	@rm -f $(OBJ)
fclean:
	@rm  -f $(NAME) $(OBJ)

re:    fclean all
