/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:59:10 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/07 13:18:21 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_philos_satisfied(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].data_lock);
		if (data->must_eat_count > 0
			&& data->philos[i].times_eaten < data->must_eat_count)
		{
			pthread_mutex_unlock(&data->philos[i].data_lock);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].data_lock);
		i++;
	}
	return (1);
}

int	philo_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].data_lock);
		if (get_current_time_in_ms() - data->philos[i].last_meal_time
			> data->time_to_die)
		{
			pthread_mutex_unlock(&data->philos[i].data_lock);
			pthread_mutex_lock(&data->print_lock);
			printf("%ld %d died\n", get_timestamp(data), data->philos[i].id);
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].data_lock);
		i++;
	}
	return (0);
}
