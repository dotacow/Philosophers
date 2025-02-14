/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:25:14 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/15 00:02:13 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_state
{
	eating,
	hungry,
	thinking,
	sleeping,
	dead
} t_state;

typedef struct s_philo
{
	t_state	state;
	int		id;

} t_philo;
typedef struct s_table
{

} t_table;

#endif