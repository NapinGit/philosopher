NAME1	=	philo
CC = clang

OBJ_DIR = obj/
SRC_DIR =	$(shell find ./srcs -type d)
# -fsanitize=address -g3
FLAGS	= -pthread -Werror -Wextra -Wall
SRC_PHILO	= thread_utils.c init_philo.c main.c parsing.c philo_action.c utils.c monitor.c philo_fork_eat.c

OBJ_PHILO	=	$(addprefix $(OBJ_DIR),$(SRC_PHILO:%.c=%.o))
vpath %.c $(SRC_DIR)

all :	$(NAME1)

$(NAME1) : $(INCLUDE) $(OBJ_PHILO)
	$(CC) $(FLAGS) $(OBJ_PHILO) -o $(NAME1)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME1)

re : fclean all