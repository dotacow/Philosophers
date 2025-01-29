CC = cc
#CFLAGS = -Wall -Wextra -Werror -I includes -pthread

SRC = philo.c

SRCS :=  $(addprefix srcs/,$(SRC))
OFILES := $(addprefix ofiles/,$(SRC:.c=.o))

NAME = philo

ofiles/%.o: srcs/%.c includes/philo.h | dirs
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -L$(LIBDIR) -lft -o $(NAME)

clean:
	rm -rf ofiles

fclean: clean
	rm -rf $(NAME)

re: fclean all

dirs:
	mkdir -p ofiles

.PHONY: dirs all clean fclean re