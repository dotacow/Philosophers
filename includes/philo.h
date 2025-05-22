/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:25:14 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/22 18:01:54 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>


typedef struct s_philo	t_philo;

typedef enum e_state
{
	eating,
	hungry,
	thinking,
	sleeping,
	satiated,
	dead,
}				t_state;

typedef struct s_clock
{
	struct timeval	start_t;
	struct timeval	eat_t;
	struct timeval	sleep_t;
	struct timeval	think_t;
	struct timeval	die_t;
}				t_clock;

typedef struct s_table
{
	/* ### SHARED RESOURCES: ### */
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	/* ### WAITER ONLY WRITE ### */
	t_clock			t_clock;
	int				eat_goal;
	int				num_philos;
	int				feast_famine;
	t_philo			**seating_list;
}				t_table;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				seat_id;
	int				first_fork;;
	int				second_fork;
	t_state			state;
	struct timeval	last_eat_t;
	int				eat_count;
	t_table			*table;
}				t_philo;

/* #### UTILS #### */
long int	ft_atoi(const char *nptr);
int			is_numeric(char **argv);
int			free_split(void **ptr, int end);
/* #### INIT #### */
int			arrange_table(char **argv, t_table *table);
int			init_philos(t_table *table);
int			init_table(char **argv, t_table *table);
/* #### ROUTINE #### */
int			wait_dinner(t_table *table);
void		*philo_routine(void *arg);
/* #### EXIT #### */
int		cleanup(t_table *table);
/* #### COLORS #### */
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PURPLE		"\033[0;35m"

#endif