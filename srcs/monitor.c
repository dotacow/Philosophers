/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:58:55 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/30 10:34:44 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_dead(t_philo *philo)
{
	long	current_time;

	current_time = get_time(philo->table->start_t);
	if (current_time - philo->last_eat_t > philo->table->t_clock.die_t)
		return (1);
	return (0);
}

int	wait_dinner(t_table *table)
{
	int	i;
	int	full_c;

	table->feast_famine = 1;
	while (table->feast_famine)
	{
		i = -1;
		full_c = 0;
		while (table->seating_list[++i])
		{
			if (is_dead(table->seating_list[i]))
			{
				mtx_printf(table, "is dead", table->seating_list[i], RED);
				table->feast_famine = 0;
				break ;
			}
			if (table->seating_list[i]->state == satiated)
				full_c++;
			if (table->eat_goal != -1 && full_c == table->num_philos)
				table->feast_famine = 0;
		}
	}
	usleep(3000);
	return (0);
}
