/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:57:12 by yokitane          #+#    #+#             */
/*   Updated: 2025/05/28 14:34:42 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	ft_atoi(const char *nptr)
{
	long int	sign;
	long int	num;
	long int	i;

	i = 0;
	num = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (num * sign);
}

static int	is_valid_char(char c, int is_first)
{
	if (is_first && c == '+')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	check_int_overflow(const char *str)
{
	int		len;
	long	num;

	len = 0;
	if (str[0] == '+')
		str++;
	while (str[len])
		len++;
	if (len > 10)
		return (0);
	if (len == 10)
	{
		num = ft_atoi(str);
		if (num > 2147483647)
			return (0);
	}
	return (1);
}

static int	validate_argument(char *arg)
{
	int	j;

	if (!arg[0])
		return (0);
	j = 0;
	while (arg[j])
	{
		if (!is_valid_char(arg[j], j == 0))
			return (0);
		j++;
	}
	return (check_int_overflow(arg));
}

int	is_numeric(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!validate_argument(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
