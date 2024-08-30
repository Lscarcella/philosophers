/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/08/30 17:38:33 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	start_simulation(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &table->philos[i]);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
}

void	*philo_routine(void *arg)
{
	t_philos *philos;

	philos = (t_philos *)arg;
	if (philos->id % 2 == 0)
			usleep(1000);
	while (philos->meal_count < philos->max_meal)
	{
		if(ft_eat(philos))
			break;
		if(ft_sleep(philos))
			break;
		if(ft_think(philos))
			break;
	}
	return (NULL);
}


int	ft_eat(t_philos *philos)
{	
	int error;

	error = 0;
	if(philos->meal_count < philos->max_meal)
	{
		pthread_mutex_lock(&philos->first_fork->fork);
		if(print_status(philos, "has taken a fork") > 0)
			error = 1;
		pthread_mutex_lock(&philos->second_fork->fork);
		if(print_status(philos, "has taken a fork") > 0)
			error = 1;
		philos->last_meal_time = get_time();
		if(print_status(philos, "is eating") > 0)
			error = 1;
		usleep_moded(philos->table->time_to_eat, philos);
		pthread_mutex_unlock(&philos->second_fork->fork);
		pthread_mutex_unlock(&philos->first_fork->fork);
		philos->meal_count++;
	}
	return(error);
}


int	ft_sleep(t_philos *philos)
{
	int error;

	error = 0;

	if(print_status(philos, "is sleeping") > 0)
		error = 1;
	usleep_moded(philos->table->time_to_sleep, philos);
	return(error);
}

int	ft_think(t_philos *philos)
{
	long long int sleep_time;
	int error;

	error = 0;
	sleep_time = 1.5 * philos->table->time_to_eat;
	if(print_status(philos, "is thinking") > 0)
		error = 1;
	if(philos->id % 2 != 0)
		usleep_moded(sleep_time, philos);
	return(error);
}



