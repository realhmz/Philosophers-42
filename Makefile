NAME = philo

C_FLAGS = -Wall -Wextra

SRC =	parce.c\
		libft_utils.c\

OBJ = $(SRC:.c=.o)

NAME : $(OBJ)
	

all : $(OBJ)
	$(CC) $(C_FLAGS) $(OBJ) -o $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@