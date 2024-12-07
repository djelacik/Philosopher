/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:31:04 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/07 12:31:42 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_take_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	print_action(ph, "has taken a fork");
	if (!ph->right_fork)
	{
		pthread_mutex_unlock(ph->left_fork);
		usleep_with_check(ph->data, ph->data->time_to_die);
		pthread_exit(NULL);
	}
	pthread_mutex_lock(ph->right_fork);
	print_action(ph, "has taken a fork");
	pthread_mutex_lock(&ph->data->simulation_lock);
	if (!ph->data->simulation_running)
	{
		pthread_mutex_unlock(&ph->data->simulation_lock);
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&ph->data->simulation_lock);
}

void	philo_eat(t_philo *ph)
{
	print_action(ph, "is eating");
	pthread_mutex_lock(&ph->data_lock);
	ph->last_meal_time = get_current_time_in_ms();
	ph->times_eaten++;
	pthread_mutex_unlock(&ph->data_lock);
	usleep_with_check(ph->data, ph->data->time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

void	philo_sleep(t_philo *ph)
{
	print_action(ph, "is sleeping");
	usleep_with_check(ph->data, ph->data->time_to_sleep);
}

void	philo_think(t_philo *ph)
{
	print_action(ph, "is thinking");
}
