/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:37:51 by lscarcel          #+#    #+#             */
/*   Updated: 2024/08/26 16:11:50 by lscarcel         ###   ########.fr       */
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

typedef struct s_table t_table;
typedef struct s_timeval t_timeval;

typedef struct s_monitor
{
	int philo_dead;
	int max_meals;
	pthread_mutex_t lock;
} t_monitor;

typedef struct s_fork
{
    pthread_mutex_t  fork;
    int fork_id;
} t_fork;

typedef struct s_philos
{
    int id;
    int meal_count;
    int last_meal_time;
    int is_full;
    t_fork *first_fork;
    t_fork *second_fork;
    pthread_t thread_id;
    t_table *table;
} t_philos;

typedef struct s_table
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int max_meals;
    int start_simulation;
	int start_time;
    int end_simulation;
    t_fork *forks;
	t_philos *philos;
	t_timeval *time;
	pthread_mutex_t print_lock;
	t_monitor *monitor;
} t_table;

typedef struct s_timeval 
{
	time_t      tv_sec; 	/*seconds*/
    suseconds_t tv_usec;    /* microseconds */
}	t_timeval;


// Main
int	main(int argc, char **argv);

// Initialisation
int	init(t_table *table, char **argv, int argc);
void    init_data(t_table *table);
int		init_struct(t_table *table, char **argv, int argc);
void    init_philos(t_table *table);
void    assign_forks(t_philos *philos, t_fork *fork, int philo_pos);

// Utils
int		only_unsigned_int(char **argv);
int		ft_atoi(const char *str);
void	*safe_malloc(size_t bytes);
long long	get_time(void);
void	print_status(t_table *table, const char *status);

//routine
void	*philo_routine(void *arg);
void	start_simulation(t_table *table);
int		is_eating(t_table *table);
void	sleep_and_think(t_table *table);

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