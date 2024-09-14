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

int	will_philo_die(t_philos *philos)
{
	if (philos->first_fork->end_time > 0 && philos->last_meal_time
		+ philos->time_to_die < philos->first_fork->end_time)
	{
		usleep((philos->last_meal_time
				+ philos->time_to_die - get_time()) * 1000);
		print_status(philos, "died");
		return (1);
	}
	else
		return (0);
}
