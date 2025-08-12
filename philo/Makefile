CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -pthread -std=c90 -fsanitize=thread

SRC = philo.c janitor.c init.c philo_routine.c sync_utils.c utils.c monitor.c

SRCS :=  $(addprefix srcs/,$(SRC))
ODIR = ofiles
OFILES := $(addprefix ofiles/,$(notdir $(SRC:.c=.o)))

NAME = philo

ofiles/%.o: srcs/%.c includes/philo.h | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME) -fsanitize=thread

clean:
	rm -rf ofiles

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(ODIR):
	mkdir -p ofiles

.PHONY: dirs all clean fclean re