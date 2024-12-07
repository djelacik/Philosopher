/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:30:28 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/07 13:19:31 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	data_lock;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	simulation_lock;
	int				simulation_running;
	pthread_mutex_t	eating_mutex;
	int				eating_philos;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

int		ft_atoi(const char *str);
int		validate_args(int argc, char **argv, t_data *data);

int		init_data(t_data *data, int argc, char **argv);
void	init_philosophers(t_data *data);

long	get_current_time_in_ms(void);
long	get_timestamp(t_data *data);

void	print_action(t_philo *philo, char *action);
void	usleep_with_check(t_data *data, int duration_ms);

int		all_philos_satisfied(t_data *data);
int		philo_died(t_data *data);
void	*monitor_philosophers(void *arg);

void	philo_take_forks(t_philo *ph);
void	philo_eat(t_philo *ph);
void	philo_sleep(t_philo *ph);
void	philo_think(t_philo *ph);
void	*philosopher_routine(void *arg);

void	start_simulation(t_data *data);

void	exit_and_free(t_data *data);

#endif