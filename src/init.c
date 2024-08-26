/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/08/26 16:15:00 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int		init(t_table *table, char **argv, int argc);
int		init_struct(t_table *table, char **argv, int argc);
void    init_data(t_table *table);
void    init_philos(t_table *table);
void    assign_forks(t_philos *philos, t_fork *fork, int philo_pos);

int	init(t_table *table, char **argv, int argc)
{
	if (init_struct(table, argv, argc) == FAIL)
		return(FAIL);
	init_data(table);
	return (SUCCESS);
}
int	init_struct(t_table *table, char **argv, int argc)
{
	memset(table, 0, sizeof(*table));
	table->number_of_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		table->max_meals = ft_atoi(argv[5]);
		if (table->max_meals < 1)
		{
			printf(COLOR_RED "Error "COLOR_WHITE": philosophers must eat\n");
			return (FAIL);
		}
	}
	else 
		table->max_meals = FALSE;
	table->start_time = get_time();
    pthread_mutex_init(&table->print_lock, NULL);
	return (SUCCESS);
}

void    init_data(t_table *table)
{
    int i;

    i = -1;
    table->end_simulation = FALSE;
    table->philos = safe_malloc(sizeof(t_philos) * table->number_of_philosophers);
    table->forks = safe_malloc(sizeof(t_fork) * table->number_of_philosophers);
    while(++i < table->number_of_philosophers)
    {
        pthread_mutex_init(&table->forks[i].fork, NULL);
        table->forks[i].fork_id = i;
    }
    init_philos(table);
}

/*
    init everything in the table struct and init a mutex for every fork
*/ 

void    init_philos(t_table *table)
{
    int i;
    t_philos *philos;

    i = -1;
    while(++i < table->number_of_philosophers)
    {
        philos = table->philos + i;
        philos->id = i + 1;
        philos->is_full = FALSE;
        philos->meal_count = 0;
        philos->table = table;
		philos->thread_id = 0;
    }
    assign_forks(philos, table->forks, i);
}
/*
Assigns forks to philosophers in a way that minimizes the risk of deadlocks.
 
By default, a philosopher attempts to pick up the fork on their right (first_fork) 
followed by the fork on their left 
(second_fork). This function introduces an asymmetry to avoid deadlocks.
 
For odd-numbered philosophers (with an odd ID), the order of picking forks is reversed: 
This asymmetry ensures that not all philosophers attempt to pick up the same fork first,
reducing the risk of a deadlock where each philosopher holds one fork 
and waits indefinitely for the second fork.
*/

void    assign_forks(t_philos *philos, t_fork *fork, int philo_pos)
{
    int philo_nbr;
    
    philo_nbr = philos->table->number_of_philosophers;
    philos->first_fork = &fork[(philo_pos + 1) % philo_nbr];
    philos->second_fork = &fork[philo_pos];
    if  (philos->id % 2)
    {
        philos->first_fork = &fork[philo_pos];
        philos->second_fork = &fork[(philo_pos + 1) % philo_nbr];
    }
}