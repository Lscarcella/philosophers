/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:00:41 by lscarcel          #+#    #+#             */
/*   Updated: 2024/08/23 14:26:51 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_table table;

	if (argc == 6 || argc == 5)
	{
		if (only_unsigned_int(argv + 1) == FALSE)
			return (FAIL);
		init(&table, argv, argc);
	}
	else
	{
		printf(COLOR_RED "Error " COLOR_WHITE": wrong arguments number\n" );
		return (FAIL);
	}
}
