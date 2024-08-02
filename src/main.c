/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:00:41 by lscarcel          #+#    #+#             */
/*   Updated: 2024/08/02 14:00:00 by lozkuro          ###   ########.fr       */
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
		init_struct(&table, argv, argc);
		init_data(&table);
	}
	else
	{
		printf(COLOR_RED "Error " COLOR_WHITE": wrong arguments number\n" );
		return (FAIL);
	}
}
