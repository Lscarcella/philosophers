/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/09/13 22:38:37 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init(t_table *table, char **argv, int argc)
{
	if (init_struct(table, argv, argc) == FAIL)
		return (FAIL);
	if (table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1)
	{
		printf(COLOR_RED "Error "COLOR_WHITE": give them a chance\n");
		return (FAIL);
	}
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->forks == NULL)
	{
		printf(COLOR_RED "Error "COLOR_WHITE": Malloc failed\n");
		return (FAIL);
	}
	table->philos = malloc(sizeof(t_philos) * table->philo_nbr);
	if (table->philos == NULL)
	{
		printf(COLOR_RED "Error "COLOR_WHITE": Malloc failed\n");
		return (FAIL);
	}
	if (init_mutex(table) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	init_struct(t_table *table, char **argv, int argc)
{
	memset(table, 0, sizeof(*table));
	table->philo_nbr = ft_atoi(argv[1]);
	if (table->philo_nbr < 1)
	{
		printf(COLOR_RED "Error "COLOR_WHITE": need at least 1 philo\n");
		return (FAIL);
	}
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
		table->max_meals = 100000;
	pthread_mutex_init(&table->fork_lock, NULL);
	pthread_mutex_init(&table->print_lock, NULL);
	return (SUCCESS);
}

int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_init(&table->forks[i].fork, NULL);
	init_philos(table);
	return (SUCCESS);
}

void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_full = FALSE;
		table->philos[i].is_dead = FALSE;
		table->philos[i].meal_count = 0;
		table->philos[i].thread_id = 0;
		table->philos[i].max_meal = table->max_meals;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].table = table;
		table->philos[i].first_fork->used == FALSE;
		table->philos[i].second_fork->used == FALSE;
	}
	assign_forks(table, table->forks);
}

void	assign_forks(t_table *table, t_fork *forks)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].first_fork = &forks[i];
		table->philos[i].second_fork = &forks[(i + 1) % table->philo_nbr];
		if (table->philos[i].id % 2 == 0)
		{
			table->philos[i].first_fork = &forks[(i + 1) % table->philo_nbr];
			table->philos[i].second_fork = &forks[i];
		}
	}
}
