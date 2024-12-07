/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:29:10 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/07 13:00:25 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*check_run(t_data *data)
{
	pthread_mutex_lock(&data->simulation_lock);
	if (!data->simulation_running)
	{
		pthread_mutex_unlock(&data->simulation_lock);
		return (NULL);
	}
	pthread_mutex_unlock(&data->simulation_lock);
	return ((void *)1);
}

static void	*check_death(t_data *data)
{
	if (philo_died(data))
	{
		pthread_mutex_lock(&data->simulation_lock);
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->simulation_lock);
		return (NULL);
	}
	return ((void *)1);
}

static void	*check_satisfied(t_data *data)
{
	if (data->must_eat_count > 0 && all_philos_satisfied(data))
	{
		pthread_mutex_lock(&data->simulation_lock);
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->simulation_lock);
		return (NULL);
	}
	return ((void *)1);
}

void	*monitor_philosophers(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (!check_run(data))
			return (NULL);
		if (!check_death(data))
			return (NULL);
		if (!check_satisfied(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
