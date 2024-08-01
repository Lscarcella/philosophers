/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:37:51 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/31 16:39:38 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

//libairies
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>


# define PHILOSOPHERS_H
# define TRUE		1
# define FALSE		0
# define SUCCESS	0
# define FAIL		1

// -- Structures -- //

typedef struct s_table
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	int			argc;
	char		**argv;
	t_philos	philos;
}	t_table;

typedef struct s_philos
{
	int			last_meal;
	int			is_full;
	t_fork		l_fork;
	t_fork		r_fork;
	pthread_t	thread_id;
	t_table		table;
}	t_philos;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}	t_fork;

//    int gettimeofday(struct timeval *tv, struct timezone *tz);
typedef struct s_timeval 
{
    time_t      tv_sec;     /* seconds */
    suseconds_t tv_usec;    /* microseconds */
}	t_timeval;
// Main
void	init_struct(t_philo *philo, char **argv, int argc);
int		only_unsigned_int(char **argv);
int		ft_atoi(const char *str);

// Utils

// Colors
# define COLOR_BLACK "\033[0;30m" // Black
# define COLOR_RED "\033[0;91m" // Red
# define COLOR_GREEN "\033[0;32m" // Green
# define COLOR_YELLOW "\033[0;33m" // Yellow
# define COLOR_BLUE "\033[0;34m" // Blue
# define COLOR_PURPLE "\033[0;35m" // Purple
# define COLOR_CYAN "\033[0;36m" // Cyan
# define COLOR_WHITE "\033[0m" // White
# define TEXT_BOLD "\033[1m" // Bold text
# define TEXT_RESET "\033[0m" // Reset text attributes

#endif