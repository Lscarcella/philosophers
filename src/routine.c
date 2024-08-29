/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/08/29 16:41:15 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *arg)
{
	t_philos *philos;

	philos = (t_philos *)arg;
	while (philos->table->ready != 1)
		usleep(1000);
	pthread_mutex_unlock(&philos->table->start_lock);
	while (philos->table->end_simulation != 1)
	{
		eat(philos);
		if (philos->meal_count >= philos->table->max_meals)
            break;
		sleep_and_think(philos);
	}
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int i;

	i = -1;
	pthread_mutex_lock(&table->start_lock);
	while (++i < table->number_of_philosophers)
		pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &table->philos[i]);
	table->ready = 1;
	i = -1;
	sauron_is_watching(table);
	while (++i < table->number_of_philosophers)
		pthread_join(table->philos[i].thread_id, NULL);
}

void	eat(t_philos *philos)
{
	if(philos->table->end_simulation != 1)
	{
		philos->is_full = TRUE;
		pthread_mutex_lock(&philos->first_fork->fork);
		print_status(philos, "has taken a fork");
		pthread_mutex_lock(&philos->second_fork->fork);
		print_status(philos, "has taken a fork");
		philos->last_meal_time = get_time();
		print_status(philos, "is eating");
		usleep(philos->table->time_to_eat * 1000);
		philos->meal_count++;
		pthread_mutex_unlock(&philos->second_fork->fork);
		pthread_mutex_unlock(&philos->first_fork->fork);
	}
}

void	usleep_moded(int time)
{
	int ct;
	ct = get_time();
	while ((ct + time) - ct < time)
	{
		usleep(100);
	}
}

void	sleep_and_think(t_philos *philos)
{
	if(philos->table->end_simulation != 1)
	{
		print_status(philos, "is sleeping");
		usleep(philos->table->time_to_sleep * 1000);
		print_status(philos, "is thinking");
	}
}


void	is_dead(t_table *table)
{
	long long current_time;
	table->end_simulation = 1;
	
	pthread_mutex_lock(&table->print_lock);
	current_time = get_time();
	printf("%lld %d is dead\n", current_time, table->philos->id);
	pthread_mutex_unlock(&table->print_lock);
}
