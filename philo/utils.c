/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:32:53 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/07 13:17:56 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

long	get_current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_timestamp(t_data *data)
{
	return (get_current_time_in_ms() - data->start_time);
}

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->simulation_lock);
	if (philo->data->simulation_running)
		printf("%ld %d %s\n", get_timestamp(philo->data), philo->id, action);
	pthread_mutex_unlock(&philo->data->simulation_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	usleep_with_check(t_data *data, int duration_ms)
{
	long	start_time;
	long	current_time;

	start_time = get_current_time_in_ms();
	while (1)
	{
		pthread_mutex_lock(&data->simulation_lock);
		if (!data->simulation_running)
		{
			pthread_mutex_unlock(&data->simulation_lock);
			break ;
		}
		pthread_mutex_unlock(&data->simulation_lock);
		current_time = get_current_time_in_ms();
		if (current_time - start_time >= duration_ms)
			break ;
		usleep(500);
	}
}

void	exit_and_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].data_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->simulation_lock);
	pthread_mutex_destroy(&data->eating_mutex);
	free(data->forks);
	free(data->philos);
}
