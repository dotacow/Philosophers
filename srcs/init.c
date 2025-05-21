/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:37:49 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/21 17:16:28 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int init_table(char **argv, t_table *table)
{
	int i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!table->forks)
		return (0);
	memset(table->forks, 0, sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	table->seating_list = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	if (!table->seating_list)
	{
		free(table->forks);
		return (0);
	}
	table->print_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->eat_goal = -1;
	table->feast_famine = 0;
	table->num_philos = ft_atoi(argv[1]);
	table->t_clock.die_t.tv_usec = ft_atoi(argv[2]);
	table->t_clock.eat_t.tv_usec = ft_atoi(argv[3]);
	table->t_clock.sleep_t.tv_usec = ft_atoi(argv[4]);
	if (argv[5])
		table->eat_goal = ft_atoi(argv[5]);
	while (++i < table->num_philos)
		table->forks[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	return (1);
}

int init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
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
		i++;
	}
	return (1);
}
