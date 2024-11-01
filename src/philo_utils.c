/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:01:30 by lozkuro           #+#    #+#             */
/*   Updated: 2024/09/14 13:05:10 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long int	get_time(void)
{
	static struct timeval	start_time = {-1, -1};
	struct timeval			actual_time;
	long long int			elapsed_time;

	if (start_time.tv_sec == -1 && start_time.tv_usec == -1)
	{
		gettimeofday(&start_time, NULL);
	}
	gettimeofday(&actual_time, NULL);
	elapsed_time = ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000))
		- ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
	return (elapsed_time);
}

int	print_status(t_philos *philos, const char *status)
{
	static int	is_dead = 0;
	int			return_value;
	long long	current_time;

	return_value = 0; 
	pthread_mutex_lock(&philos->table->print_lock);
	if (is_philo_dead(philos) == TRUE)
		is_dead++;
	current_time = get_time();
	if (is_dead == 0)
		printf("%lld %d %s\n", current_time, philos->id, status);
	else if (is_dead == 1)
	{
		printf("%lld %d died\n", current_time, philos->id);
		is_dead++;
	}
	return_value = is_dead;
	pthread_mutex_unlock(&philos->table->print_lock);
	return (return_value);
}

int	is_philo_dead(t_philos *philos)
{
	if (get_time() - philos->last_meal_time >= philos->time_to_die)
		return (TRUE);
	else
		return (FALSE);
}

void	usleep_moded(long long int time, t_philos *philos)
{
	long long int	current_time;

	current_time = get_time();
	while (get_time() - current_time < time && is_philo_dead(philos) == FALSE)
		usleep(1000);
}

int fork_statement(t_philos *philos, char *order)
{
	pthread_mutex_lock(&philos->table->fork_lock);
	if (strncmp(order, "set", 1) == 0)
	{
		philos->first_fork->used = TRUE;
		philos->second_fork->used = TRUE;
	}
	else if (strncmp(order, "unset", 1) == 0)
	{
		philos->first_fork->used = FALSE;
		philos->second_fork->used = FALSE;
	}
	else if (strncmp(order, "check", 1) == 0)
	{
		if (philos->first_fork->used == FALSE && philos->second_fork->used == FALSE)
		{
			pthread_mutex_unlock(&philos->table->fork_lock);
			return(FALSE);
		}
		else
		{
			pthread_mutex_unlock(&philos->table->fork_lock);
			return(TRUE);
		}
	}
	pthread_mutex_unlock(&philos->table->fork_lock);
	return(0);
}