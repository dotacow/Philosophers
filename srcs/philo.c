/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:24:33 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/29 17:09:24 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	arrange_table(char **argv, t_table *table)
{
	if (!init_table(argv, table))
		return (0);
	if (!init_philos(table))
	{
		free(table->forks);
		free(table->seating_list);
		return (0);
	}
	gettimeofday(&table->start_t, NULL);
	if (!init_threads(table))
		return (cleanup(table));
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if ((argc == 5 || argc == 6) && is_numeric(argv))
	{
		if (arrange_table(argv, &table))
			wait_dinner(&table);
		cleanup(&table);
		return (0);
	}
	write(2, "usage: ./philo n_philo t_die t_eat t_sleep [n_min_eat_philo]\n",
		61);
	return (1);
}
