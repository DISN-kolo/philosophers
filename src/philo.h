/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:22:27 by akozin            #+#    #+#             */
/*   Updated: 2024/03/11 14:36:00 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * all the times are calculated in microseconds, 1 micro-s = 1/1000th of a ms
 * hence the long variables
 */
#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef enum e_timecode
{
	SEC,
	MILSEC,
	MICSEC,
}	t_timecode;

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
	int			meals_counter;
	int			full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*last_fork;
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
 * this is basically a bool
 *
 * ready to start - self explanatory. indicates that all threads have been
 * launched and are revving. ready to drop the clutch and burn some tires!
 * p.s. r.i.p. transmission or something idk i'm not an auto guy
 *
 * data mtx is used to avoid races while multithreadedly doing stuff to data
 *
 * entry format:
 * 		./philo <philo N> <T die> <T eat> <T sleep> [meals limit N]
 * 		argv[0] argv[1]   argv[2] argv[3] argv[4]   argv[5]
 */
struct s_data
{
	int		philo_number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_limit_number;
	long	start_simulation;
	int		end_simulation;
	int		ready_to_start;
	t_mtx	data_mtx;
	t_fork	*forks;
	t_philo	*philos;
};
#endif
