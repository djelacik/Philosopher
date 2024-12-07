/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:24:44 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/07 12:26:16 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int argc, char **argv)
{
	if (validate_args(argc, argv, data))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
	{
		if (data->forks)
			free(data->forks);
		if (data->philos)
			free(data->philos);
		return (1);
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->simulation_lock, NULL);
	pthread_mutex_init(&data->eating_mutex, NULL);
	data->eating_philos = 0;
	data->simulation_running = 1;
	return (0);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].times_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		if (data->num_philos == 1)
			data->philos[i].right_fork = NULL;
		else
			data->philos[i].right_fork = &data->forks[(i + 1)
				% data->num_philos];
		data->philos[i].data = data;
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].data_lock, NULL);
		i++;
	}
}
