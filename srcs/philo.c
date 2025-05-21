/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:24:33 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/21 17:18:45 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
/**
the dining philosphers problem.
what I need to do:
		parse and validate user input
		set up table
			seat philos   (init threads)
			arrange forks (init mutexes)
			assosciate philos with forks
	start routine (print each step with timestamp)
		group dinner (n != 2):
			philo picks up first fork to l/r (to elimante circular wait)
				philo picks up second fork if possible
				eats for t_eat
				philo sleeps for t_sleep
				philo thinks for t_think
		couple dinner (n == 2):
			the philos will take turns eating.
		along side all this, runs a monitor thread.
		 every 5ms, runs a poll:
			if any philo is dead -->	end_dinner.
			if eat_goal && all philos are @satiated:	--> end_dinner.
*/




int arrange_table(char **argv, t_table *table)
{
	if (!init_table(argv, table))
		return (0);
	if (!init_philos(table))
		{
			free(table->forks);
			free(table->seating_list);
			return (0);
		}
	if (!init_threads(table))
	{
		
	}
		return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if ((argc == 5 || argc == 6) && is_numeric(argv))
	{
		if (arrange_table(argv, &table))
				return (start_dinner());
		return (-1);
	}
	write(2, "usage: ./philo n_philo t_die t_eat t_sleep [n_min_eat_philo]\n",
		61);
	return (1);
}
