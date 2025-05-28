/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:25:14 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/28 18:10:53 by yokitane         ###   ########.fr       */
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
# include <stdatomic.h>


typedef struct s_philo	t_philo;

typedef enum e_state
{
	hungry,
	satiated,
	dead,
}				t_state;

typedef struct s_clock
{
	long	eat_t;
	long	sleep_t;
	long	think_t;
	long	die_t;
}				t_clock;

/**
	@feast_famine:
		1: sim ongoing
		0: sim ended/not started yet
	@start_t:
	 our local epoch
*/
typedef struct s_table
{
	/* ### SHARED RESOURCES: ### */
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	/* ### WAITER ONLY WRITE ### */
	t_clock			t_clock;
	struct timeval	start_t;
	int				eat_goal;
	int				num_philos;
	_Atomic int		feast_famine;
	t_philo			**seating_list;
}				t_table;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				seat_id;
	int				first_fork;
	int				second_fork;
	t_state			state;
	long			last_eat_t;
	int				eat_count;
	t_table			*table;
}				t_philo;

/* #### UTILS #### */
long int	ft_atoi(const char *nptr);
int			is_numeric(char **argv);
int			free_split(void **ptr, int end);
/* #### TIME & SYNC */
void		ft_usleep(long time_in_ms, t_table *table);
void		mtx_printf(t_table *table, const char *str, t_philo *philo);
long		get_time(struct timeval start);
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
# define RED		"\033[0;31m"//death
# define GREEN		"\033[0;32m"//taken a fork
# define YELLOW		"\033[0;33m"//sleep
# define PURPLE		"\033[0;35m"//thinking
# define BLUE		"\033[0;34m"

#endif