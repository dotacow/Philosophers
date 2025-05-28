/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:03 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/28 15:03:10 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->state = hungry;
	if (philo->seat_id % 2)
		usleep(60);
	philo->last_eat_t = get_time(philo->table->start_t);
	while(philo->table->feast_famine)// data race?
	{

	}
}
