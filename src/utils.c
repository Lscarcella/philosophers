/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:06:39 by lscarcel          #+#    #+#             */
/*   Updated: 2024/09/13 22:38:31 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	only_unsigned_int(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
		{
			i++;
			printf(COLOR_RED "Error " COLOR_WHITE": argv[%d] is empty\n", i);
			return (FALSE);
		}
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error : args must be unsigned integers\n");
				return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	the_end(t_table *table)
{
	int	i;

	i = -1;
	free(table->philos);
	table->philos = NULL;
	free(table->forks);
	table->forks = NULL;
	pthread_mutex_destroy(&table->end_lock);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->meal_lock);
}
