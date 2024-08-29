/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sauron.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/08/29 16:24:38 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void sauron_is_watching(t_table *table)
{
	int i;

	 while (table->end_simulation != 1)
    {
		i = -1;
		while (++i < table->number_of_philosophers)
        {
            if (get_time() - table->philos[i].last_meal_time >= table->time_to_die)
            {
               is_dead(table);
			   break;
            }
            if (table->philos[i].meal_count >= table->max_meals)
                table->monitor->full_philos++;
        }
        if (table->monitor->full_philos == table->number_of_philosophers)
        {
           	table->end_simulation = 1;
			break;
        }
   		usleep(1000);
    }
}

void the_end(t_table *table)
{
	int i;

	i = -1;
	free(table->philos);
	table->philos = NULL;
	free(table->forks);
	table->forks = NULL;
}