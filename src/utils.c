/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:06:39 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/29 11:42:14 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_struct(t_philo *philo, char **argv, int argc)
{
	memset(&philo->args, 0, sizeof(philo->args));
	philo->args.argc = argc;
	philo->args.argv = argv;
	philo->args.number_of_philosophers = ft_atoi(argv[1]);
	philo->args.time_to_die = ft_atoi(argv[2]);
	philo->args.time_to_eat = ft_atoi(argv[3]);
	philo->args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->args.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else 
		philo->args.number_of_times_each_philosopher_must_eat = -1;
}

int	only_unsigned_int(char **argv)
{
	int	i;
	int	j;
	
	i = 0;
	
	while(argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (FALSE);
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
