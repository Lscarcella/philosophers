/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/08/26 15:59:56 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    int i;

	i = -1;
    while (1)
    {
        pthread_mutex_lock(&table->monitor->lock);
		while (++i < table->number_of_philosophers)
        {
            if (get_time() - table->philos[i].last_meal_time > table->time_to_die)
            {
                table->monitor->philo_dead = 1;
                pthread_mutex_unlock(&table->monitor->lock);
                return (NULL);
            }
            if (table->philos[i].meal_count >= table->max_meals)
                table->monitor->max_meals++;
        }
        if (table->monitor->max_meals == table->number_of_philosophers)
        {
            table->monitor->philo_dead = 1;
            pthread_mutex_unlock(&table->monitor->lock);
            return (NULL);
        }
        pthread_mutex_unlock(&table->monitor->lock);
        usleep(1000);
    }
    return (NULL);
}
