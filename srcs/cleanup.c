/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:22:14 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/21 17:31:55 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"


void philo_cleanup(t_philo *philo)
{
	if (philo)
	{
		
		thread_join(philo->thread_id, NULL);
		free(philo);
	}
}
}

int free_split(void **ptr, int end)
{
	int	i;

	if (!ptr)
		return (0);
	i = 0;
	while (i < end)
	{
		if (ptr[i])
			free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
	return (0);
}

void cleanup(t_table *table)
{

}
