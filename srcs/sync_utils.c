/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:35:09 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/28 15:11:05 by yokitane         ###   ########.fr       */
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
	return ((int)(get_timestamp_in_ms() - ((start.tv_sec * 1000)// 1197.1
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
/*
 very confusing, but the negation is to maintan coherent grammer.
 this is because of you hamza.
*/
int is_stop(t_table *table)
{
	int stop = 0;
	pthread_mutex_lock(&table->stop_lock);
	stop = !table->feast_famine;
	pthread_mutex_unlock(&table->stop_lock);
	return stop;
}
