/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:37:51 by lscarcel          #+#    #+#             */
/*   Updated: 2024/09/13 21:35:14 by lozkuro          ###   ########.fr       */
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
# include <stdbool.h>

# define PHILOSOPHERS_H
# define TRUE		1
# define FALSE		0
# define SUCCESS	0
# define FAIL		1
# define DEAD		0

// -- Structures -- //

typedef struct s_table		t_table;
typedef struct s_timeval	t_timeval;

typedef struct s_monitor
{
	int	philo_dead;
	int	full_philos;
}	t_monitor;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					end_time;
	int					fork_id;
}	t_fork;

typedef struct s_philos
{
	int			id;
	int			is_dead;
	int			is_full;
	int			meal_count;
	int			max_meal;
	int			time_to_die;
	int			last_meal_time;
	pthread_t	thread_id;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
}	t_philos;

typedef struct s_table
{
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long long int		max_meals;
	int					start_simulation;
	int					start_time;
	int					end_simulation;
	int					ready;
	pthread_mutex_t		end_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		print_lock;
	t_fork				*forks;
	t_philos			*philos;
	t_timeval			*time;
}	t_table;

// Main
int			main(int argc, char **argv);

// Utils
int			only_unsigned_int(char **argv);
int			ft_atoi(const char *str);
void		the_end(t_table *table);

// Philo_utils
long long	get_time(void);
int			print_status(t_philos *philos, const char *status);
void	usleep_moded(long long int time, t_philos *philos);
int			is_philo_dead(t_philos *philos);

// Initialisation
int			init(t_table *table, char **argv, int argc);
int			init_data(t_table *table);
int			init_struct(t_table *table, char **argv, int argc);
void		init_philos(t_table *table);
void		assign_forks(t_table *table, t_fork *forks);

// Routine
void		*philo_routine(void *arg);
void		start_simulation(t_table *table);
int			ft_eat(t_philos *philos);
int			ft_sleep(t_philos *philos);
int			ft_think(t_philos *philos);

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