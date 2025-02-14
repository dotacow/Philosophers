/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:24:33 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/14 23:32:55 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//the dining philosphers problem.
//what I need to do:
	// parse and validate user input
	// set up table
		// seat philos
		// arrange forks
	//start routine (print each step with realtime-timestamp)
		// each philo has death timer
		// philo picks up first fork to l/r
			//depends on seating parity.
		// philo picks up second fork if possible
			//eats for t_eat and resets death timer.
		// philo thinks
		// philo sleeps.
	// along side all this, runs a monitor thread.
		// if any philo dies, simulation stops.
	//keep track of resouces to free to exit gracefully at any point.
int main(int argc, char **argv)
{
	if (argc == 5 || argc == 4)
	{
		arrange_table();
		start_dinner();
		return (0);
	}
	write(2,"usage: ./philo n_philo t_die t_eat t_sleep [n_min_eat_philo]\n",61);
	return (1);
}