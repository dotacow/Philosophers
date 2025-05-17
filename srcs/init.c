/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:37:49 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/17 20:48:49 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int init_table(char **argv, t_table *table)
{
	int i;

	i = 0;
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
	return (1);
}
