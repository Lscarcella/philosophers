/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/08/29 15:28:04 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int		init(t_table *table, char **argv, int argc);
int		init_struct(t_table *table, char **argv, int argc);
int		init_data(t_table *table);
void    init_philos(t_table *table);
void    assign_forks(t_table *table, t_fork *fork);

int	init(t_table *table, char **argv, int argc)
{
	if (init_struct(table, argv, argc) == FAIL)
		return(FAIL);
	table->forks = malloc(sizeof(t_fork) * table->number_of_philosophers);
	if ( table->forks == NULL)
	{
		printf(COLOR_RED "Error "COLOR_WHITE": Malloc failed\n");
		return (FAIL);
	}
	table->philos = malloc(sizeof(t_philos) * table->number_of_philosophers);
	if ( table->philos == NULL)
	{
		printf(COLOR_RED "Error "COLOR_WHITE": Malloc failed\n");
		return (FAIL);
	}
	table->monitor = malloc(sizeof(t_monitor));
	if ( table->monitor == NULL)
	{
		printf(COLOR_RED "Error "COLOR_WHITE": Malloc failed\n");
		return (FAIL);
	}
	if (init_data(table) == FAIL)
		return(FAIL);
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
		table->max_meals = 1000;
	table->start_time = get_time();
    pthread_mutex_init(&table->print_lock, NULL);
    pthread_mutex_init(&table->start_lock, NULL);
	return (SUCCESS);
}

int    init_data(t_table *table)
{
    int i;

    i = -1;
    table->end_simulation = FALSE;
    while(++i < table->number_of_philosophers)
    {
        pthread_mutex_init(&table->forks[i].fork, NULL);
        table->forks[i].fork_id = i;
    }
    init_philos(table);
	return (SUCCESS);
}

void    init_philos(t_table *table)
{
    int i;

    i = -1;
    while(++i < table->number_of_philosophers)
    {
        table->philos[i].id = i + 1;
        table->philos[i].is_full = FALSE;
        table->philos[i].meal_count = 0;
        table->philos[i].table = table;
        table->philos[i].thread_id = 0;
    }
    assign_forks(table, table->forks);
}

void assign_forks(t_table *table, t_fork *forks)
{
    int i;

	i = -1;
    while (++i < table->number_of_philosophers)
    {
        table->philos[i].first_fork = &forks[i];
        table->philos[i].second_fork = &forks[(i + 1) % table->number_of_philosophers];
        if (table->philos[i].id % 2 == 0)
        {
            table->philos[i].first_fork = &forks[(i + 1) % table->number_of_philosophers];
            table->philos[i].second_fork = &forks[i];
        }
    }
}
