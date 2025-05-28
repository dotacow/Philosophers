/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:35:09 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/28 17:58:15 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long get_time(struct timeval start)
{
	return ((int)(get_timestamp_in_ms() - ((start.tv_sec * 1000)
			+ (start.tv_usec / 1000))));
}

void ft_usleep(long time_in_ms, t_table *table)
{
	struct timeval	start;
	long			current_time;

	gettimeofday(&start, NULL);
	current_time = get_time(start);
	while (current_time < time_in_ms && table->feast_famine)
	{
		usleep(100);
		current_time = get_time(start);
	}
}

void mtx_printf(t_table *table, const char *str, t_philo *philo)
{
	long timestamp;

	timestamp = get_time(table->start_t);
	pthread_mutex_lock(&table->print_lock);
	printf("%ld %d %s\n", timestamp, philo->seat_id + 1, str);
	pthread_mutex_unlock(&table->print_lock);
}