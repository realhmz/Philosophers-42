NAME = philo


C_FLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3
SRC =	parce.c\
		libft_utils.c\
		philo.c\
		utils.c\
		routine.c\
		more_utils.c\
		eat.c\
		utils_2.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)
	

$(NAME) : $(OBJ)
	 $(CC) $(C_FLAGS) $(OBJ) -o $(NAME)  

	

.c.o :
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
fclean:
	@rm  -f $(NAME) $(OBJ)

re:    fclean all

.SECONDARY: $(OBJ)