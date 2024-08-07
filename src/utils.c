/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:06:39 by lscarcel          #+#    #+#             */
/*   Updated: 2024/08/02 14:03:14 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	only_unsigned_int(char **argv)
{
	int	i;
	int	j;
	
	i = 0;
	while(argv[i])
	{
		if (argv[i][0] == '\0')
		{
			i++;
			printf(COLOR_RED "Error " COLOR_WHITE": argv[%d] is empty\n", i);
			return (FALSE);
		}
		j = 0;
		while(argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf(COLOR_RED "Error " COLOR_WHITE": args must be unsigned integers\n" );
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

void	*safe_malloc(size_t bytes)
{
	char *memory;

	memory = malloc(sizeof(char) * bytes);
	if (memory == NULL)
	{
		printf("Error with the malloc of %ld bytes\n", bytes);
		return NULL;
	}
	return (memory);
}