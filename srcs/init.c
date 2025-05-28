/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:37:49 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/28 20:50:24 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void table_init_helper(char **argv, t_table *table)
{
	table->print_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->eat_goal = -1;
	table->feast_famine = 0;
	table->num_philos = ft_atoi(argv[1]);
	table->t_clock.die_t = ft_atoi(argv[2]);
	table->t_clock.eat_t = ft_atoi(argv[3]);
	table->t_clock.sleep_t = ft_atoi(argv[4]);
	if (argv[5])
		table->eat_goal = ft_atoi(argv[5]);
}
t_janitor *init_janitor(t_table *table)
{
	t_janitor *janitor;
	int i;

	i = -1;
	janitor = malloc(sizeof(t_janitor));
	if (!janitor)
		return (NULL);
	janitor->fork_indc = malloc(sizeof(int) * table->num_philos);
	if (!janitor->fork_indc)
	{
		free(janitor);
		return (NULL);
	}
	memset(janitor->fork_indc, 1, sizeof(int) * table->num_philos);
	janitor->print_lock_indc = 1;
	while (++i < table->num_philos)
	{
		table->forks[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		/* table->janitor->fork_indc[i] = i; */
	}
	return (janitor);
}

int init_table(char **argv, t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!table->forks)
		return (0);
	table->seating_list = malloc(sizeof(t_philo *) * ft_atoi(argv[1]) + 1);
	if (!table->seating_list)
	{
		free(table->forks);
		return (0);
	}
	table_init_helper(argv, table);
	table->janitor = init_janitor(table);
	if (!table->janitor)
	{
		free(table->forks);
		free(table->seating_list);
		return (0);
	}
	table->feast_famine = 1;// CHANGE!
	return (1);
}

int init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		table->seating_list[i] = malloc(sizeof(t_philo));
		if (!table->seating_list[i])
			return (free_split((void *)table->seating_list, i));
		table->seating_list[i]->seat_id = i;
		if (i % 2)
			table->seating_list[i]->first_fork = i;
		else
			table->seating_list[i]->first_fork = (i + 1) % table->num_philos;
		if (i % 2)
			table->seating_list[i]->second_fork = (i + 1) % table->num_philos;
		else
			table->seating_list[i]->second_fork = i;
		table->seating_list[i]->eat_count = 0;
		table->seating_list[i]->state = hungry;
		table->seating_list[i]->table = table;
		table->seating_list[i]->thread_id = 0;
	}
	return (1);
}
int init_threads(t_table *table)
{
	int i;

	i = 0;
	while (i < table->num_philos)
	{
		table->seating_list[i]->thread_id = (pthread_t)NULL;
		if (pthread_create(&table->seating_list[i]->thread_id, NULL,
				(void *)philo_routine, (void *)table->seating_list[i])
				!= 0)
			return (0);
		i++;
	}
	return (1);
}
