/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:55 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/09 11:56:50 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-2);
		if (result > (LONG_MAX - (*str - '0')) / 10)
			return (-2);
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result * sign > INT_MAX || result * sign < INT_MIN)
		return (-2);
	return ((int)(result * sign));
}

int	validate_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments.\n");
		return (1);
	}
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->must_eat_count = ft_atoi(argv[5]);
		data->must_eat_flag = 1;
	}
	else
		data->must_eat_count = 0;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (data->must_eat_count <= 0 && data->must_eat_flag))
	{
		printf("Error: Invalid argument values.\n");
		return (1);
	}
	return (0);
}
