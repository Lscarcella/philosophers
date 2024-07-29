/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:00:41 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/29 11:42:31 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_philo philo;

	if (argc == 6 || argc == 5)
	{
		if (only_unsigned_int(argv + 1) == FALSE)
		{
			printf(COLOR_RED "Error " COLOR_WHITE": args must be unsigned integers\n" );
			return (FAIL);
		}
		init_struct(&philo, argv, argc);
	}
	else
	{
		printf(COLOR_RED "Error " COLOR_WHITE": wrong arguments number\n" );
		return (FAIL);
	}
}
