/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:00:41 by lscarcel          #+#    #+#             */
/*   Updated: 2024/09/14 13:00:15 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 6 || argc == 5)
	{
		if (only_unsigned_int(argv + 1) == FALSE)
			return (FAIL);
		if (init(&table, argv, argc) == FAIL)
			return (FAIL);
		start_simulation(&table);
		the_end(&table);
	}
	else
	{
		printf(COLOR_RED "Error " COLOR_WHITE": wrong arguments number\n" );
		return (FAIL);
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_create(&table->philos[i].thread_id, NULL,
			philo_routine, &table->philos[i]);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
}
