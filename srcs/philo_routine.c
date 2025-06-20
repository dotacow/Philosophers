/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:03 by yokitane          #+#    #+#             */
/*   Updated: 2025/06/17 14:48:15 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->first_fork]);
	mtx_printf(philo->table, "has taken a fork", philo, GREEN);
	if (!philo->table->feast_famine || philo->table->num_philos == 1)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->table->forks[philo->second_fork]);
	mtx_printf(philo->table, "has taken a fork", philo, GREEN);
	if (philo->table->feast_famine)
	{
		mtx_printf(philo->table, "is eating", philo, BLUE);
		philo->last_eat_t = get_time(philo->table->start_t);
		ft_usleep(philo->table->t_clock.eat_t, philo->table);
	}
	pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->second_fork]);
	philo->eat_count++;
	if (philo->eat_count >= philo->table->eat_goal)
		philo->state = satiated;
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->state = hungry;
	while (!philo->table->feast_famine)
		usleep(50);
	if (philo->seat_id % 2)
		ft_usleep(5, philo->table);
	philo->last_eat_t = get_time(philo->table->start_t);
	while (philo->table->feast_famine)
	{
		if (philo->table->feast_famine)
			if (!pick_up_forks(philo))
				return (NULL);
		if (philo->table->feast_famine)
		{
			mtx_printf(philo->table, "is sleeping", philo, YELLOW);
			ft_usleep(philo->table->t_clock.sleep_t, philo->table);
		}
		mtx_printf(philo->table, "is thinking", philo, PURPLE);
		usleep(500);
	}
	return (NULL);
}
