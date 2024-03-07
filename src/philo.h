/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:22:27 by akozin            #+#    #+#             */
/*   Updated: 2024/03/07 15:58:02 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

/*
 * id is the number of the philo
 *
 * meals counter - how many meals did he eat
 *
 * full - if the philo has eaten max meals (max meals is non-obligatory for
 * entry. they can eat infinitely)
 *
 * last meal time - time passed from last meal. death checks need it
 *
 * pointers to the left n right forks are obvious
 *
 * thread id is the thread id of the current philo
 */
typedef struct s_philo
{
	int			id;
	long		meals_counter;
	int			full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

/*
 * program data basically
 *
 * if meals limit number == -1 => we don't have a limit
 *
 * start simulation is the time when the simulation started. we'll need it
 * to count current RELATIVE time.
 *
 * end simulation - whether the sim has ended or not (a philo dies or they
 * all get full)
 */
struct s_data
{
	long	philo_number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_limit_number;
	long	start_simulation;
	int		end_simulation;
	t_fork	*forks;
	t_philo	*philos;
};
#endif
