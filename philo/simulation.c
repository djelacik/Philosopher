/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:35:22 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/07 13:18:08 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_monitor_thread(t_data *data, pthread_t *monitor_thread)
{
	if (pthread_create(monitor_thread, NULL, monitor_philosophers, data) != 0)
		return (1);
	return (0);
}

static int	create_philosopher_threads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philosopher_routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	join_philosopher_threads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	start_simulation(t_data *data)
{
	pthread_t	*threads;
	pthread_t	monitor_thread;

	threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!threads)
		return ;
	data->start_time = get_current_time_in_ms();
	if (create_monitor_thread(data, &monitor_thread))
	{
		free(threads);
		return ;
	}
	if (create_philosopher_threads(data, threads))
	{
		free(threads);
		return ;
	}
	pthread_join(monitor_thread, NULL);
	join_philosopher_threads(data, threads);
	free(threads);
}
