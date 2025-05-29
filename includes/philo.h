/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:25:14 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/29 20:52:36 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo		t_philo;
typedef struct s_janitor	t_janitor;

typedef enum e_state
{
	hungry,
	satiated,
	dead,
}							t_state;

typedef struct s_clock
{
	long					eat_t;
	long					sleep_t;
	long					die_t;
}							t_clock;

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
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_lock;
	/* ### WAITER ONLY WRITE ### */
	struct timeval			start_t;
	t_clock					t_clock;
	t_philo					**seating_list;
	t_janitor				*janitor;
	int						eat_goal;
	int						num_philos;
	_Atomic int				feast_famine;
}							t_table;

typedef struct s_philo
{
	t_table					*table;
	pthread_t				thread_id;
	_Atomic t_state			state;
	_Atomic long			last_eat_t;
	int						seat_id;
	int						first_fork;
	int						second_fork;
	int						eat_count;
}							t_philo;

/**
	clean up only access.
*/
typedef struct s_janitor
{
	int						*fork_indc;
	int						print_lock_indc;
}							t_janitor;

/* #### UTILS #### */
long int					ft_atoi(const char *nptr);
int							is_numeric(char **argv);
int							free_split(void **ptr, int end);
/* #### TIME & SYNC */
void						ft_usleep(long time_in_ms, t_table *table);
void						mtx_printf(t_table *table, char *str,
								t_philo *philo, char *color);
long						get_time(struct timeval start);
/* #### INIT #### */
int							arrange_table(char **argv, t_table *table);
int							init_philos(t_table *table);
int							init_table(char **argv, t_table *table);
int							init_threads(t_table *table);
/* #### ROUTINE #### */
int							wait_dinner(t_table *table);
void						*philo_routine(void *arg);
/* #### MONITOR #### */
int							wait_dinner(t_table *table);
/* #### EXIT #### */
int							cleanup(t_table *table);
/* #### COLORS #### */
# define RED "\033[0;31m" // death
# define GREEN "\033[0;32m" // taken a fork
# define YELLOW "\033[0;33m" // sleep
# define PURPLE "\033[0;35m" // thinking
# define BLUE "\033[0;34m" // eating

#endif