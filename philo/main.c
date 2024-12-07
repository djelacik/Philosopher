/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:31:00 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/07 12:52:54 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&ph->data->simulation_lock);
		if (!ph->data->simulation_running)
		{
			pthread_mutex_unlock(&ph->data->simulation_lock);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&ph->data->simulation_lock);
		philo_think(ph);
		philo_take_forks(ph);
		philo_eat(ph);
		philo_sleep(ph);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (init_data(&data, argc, argv))
	{
		printf("Error: Initialization failed.\n");
		return (1);
	}
	data.start_time = get_current_time_in_ms();
	init_philosophers(&data);
	start_simulation(&data);
	i = 0;
	while (i < data.num_philos)
	{
		pthread_mutex_destroy(&data.forks[i]);
		pthread_mutex_destroy(&data.philos[i].data_lock);
		i++;
	}
	pthread_mutex_destroy(&data.print_lock);
	pthread_mutex_destroy(&data.simulation_lock);
	pthread_mutex_destroy(&data.eating_mutex);
	free(data.forks);
	free(data.philos);
	return (0);
}
