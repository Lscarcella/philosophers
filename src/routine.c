/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/09/14 13:02:00 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	if (philos->id % 2 == 0)
		usleep(1000);
	while (philos->meal_count < philos->max_meal)
	{
		if (ft_think(philos) == 1)
			break ;
		if (ft_eat(philos) == 1)
			break ;
		if (ft_sleep(philos) == 1)
			break ;
	}
	return (NULL);
}

int	ft_eat(t_philos *philos)
{
	int	error;

	error = 0;
	pthread_mutex_lock(&philos->first_fork->fork);
	if (print_status(philos, "has taken a fork") > 0)
		error = 1;
	if (philos->table->philo_nbr == 1)
	{
		usleep(philos->time_to_die);
		pthread_mutex_unlock(&philos->first_fork->fork);
		return(1);
	}
	pthread_mutex_lock(&philos->second_fork->fork);
	if (print_status(philos, "has taken a fork") > 0)
		error = 1;
	if (print_status(philos, "is eating") > 0)
		error = 1;
	philos->last_meal_time = get_time();
	usleep_moded(philos->table->time_to_eat, philos);
	pthread_mutex_unlock(&philos->second_fork->fork);
	pthread_mutex_unlock(&philos->first_fork->fork);
	fork_statement(philos, "unset");
	philos->meal_count++;
	return (error);
}

int	ft_sleep(t_philos *philos)
{
	int	error;

	error = 0;
	if (print_status(philos, "is sleeping") > 0)
		error = 1;
	usleep_moded(philos->table->time_to_sleep, philos);
	return (error);
}

int	ft_think(t_philos *philos)
{
	int	error;

	error = 0;
	if (print_status(philos, "is thinking") > 0)
		error = 1;
	if (philos->table->philo_nbr % 2 != 0)
		usleep_moded(philos->table->time_to_eat, philos);
	while (fork_statement(philos, "check") == TRUE)
	{
		if(is_philo_dead(philos) == TRUE)
		{
			print_status(philos, "died");
			return(1);
		}
		usleep(1000);
	}
	fork_statement(philos, "set");
	return (error);
}
