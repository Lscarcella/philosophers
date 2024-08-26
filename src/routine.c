/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/08/26 16:24:53 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *arg)
{
	t_table *table;

	table = (t_table *)arg;
	while (!table->end_simulation)
	{
		is_eating(table);
		if (table->philos->meal_count >= table->max_meals)
        {
            table->philos->is_full = TRUE;
            break;
        }
		sleep_and_think(table);
	}
	return (NULL);
}
void	start_simulation(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->number_of_philosophers)
		pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &table->philos[i]);
	i = -1;
	while (++i < table->number_of_philosophers)
		pthread_join(table->philos[i].thread_id, NULL);
}

int	is_eating(t_table *table)
{
	pthread_mutex_lock(&table->philos->first_fork->fork);
	print_status(table, "has taken a fork");
	pthread_mutex_lock(&table->philos->second_fork->fork);
	print_status(table, "has taken a fork");
	print_status(table, "is eating");
	table->philos->last_meal_time = get_time();
	usleep(table->time_to_eat * 1000);
	table->philos->meal_count++;
	pthread_mutex_unlock(&table->philos->second_fork->fork);
	pthread_mutex_unlock(&table->philos->first_fork->fork);

	return (TRUE);
}


void	sleep_and_think(t_table *table)
{
	print_status(table, "is sleeping");
	usleep(table->time_to_sleep * 1000);
	print_status(table, "is thinking");
}


int	is_dead(t_table *table)
{
	long time_since_last_meal;
	
	if (table->philos->is_full == TRUE)
		return(FALSE);

	time_since_last_meal = get_time() - table->philos->last_meal_time;
	if (time_since_last_meal > table->time_to_die)
		return(TRUE);
	return(FALSE);
}
