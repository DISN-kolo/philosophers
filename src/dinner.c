/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/11 17:44:30 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

//	in src/safe_funcs.c
int		thread_try(pthread_t *th, void *(*f)(void *), void *data,
			t_opcode opcode);
//	in src/set.c
void	mtx_set_i(t_mtx *mutex, int *dest, int val);
void	mtx_set_l(t_mtx *mutex, long *dest, long val);
int		sim_finished(t_data *data);
//	in src/sync_utils.c
void	wait_all_threads(t_data *data);
//	in src/utils.c
void	pusleep(long usec, t_data *data);
long	gettime(t_timecode timecode);
//	in src/write.c
void	write_status(t_status status, t_philo *ph);

//	TODO????? WHY
void	think(t_philo *ph)
{
	write_status(THINKING, ph);
}

/*
 * 1. fork grabbin
 * 2. eat: write, upd last meal, udp meal count
 * 3. release forks
 */
void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->first_fork->fork);
	write_status(TAKE_F_FORK, ph);
	pthread_mutex_lock(&ph->second_fork->fork);
	write_status(TAKE_S_FORK, ph);
	mtx_set_l(&ph->ph_mtx, &ph->last_meal_time, gettime(MILSEC));
	ph->meals_counter++;
	write_status(EATING, ph);
	pusleep(ph->data->time_to_eat, ph->data);
	if (ph->data->meals_limit_number > 0
			&& ph->meals_counter == ph->data->meals_limit_number)
		mtx_set_i(&ph->ph_mtx, &ph->full, 1);
	pthread_mutex_unlock(&ph->first_fork->fork);
	pthread_mutex_unlock(&ph->second_fork->fork);
}
/*
 * sim plan:
 * 1. check for fullnes (like in "eaten X times")
 * 2. eat (if we didn't quit at 1)
 * 3. eepy time
 * 4. methinks
 */
void	*dinner_sim(void *d)
{
	t_philo	*ph;

	ph = (t_philo *)d;
	wait_all_threads(ph->data);
	while (!sim_finished(ph->data))
	{
		if (ph->full) // TODO thread safety ??
			break ;
		eat(ph);
		write_status(SLEEPING, ph);
		pusleep(ph->data->time_to_sleep, ph->data);
		think(ph); // TODO
	}
	return (0);
}

/*
 * is there 0 meals specified?
 * just return.
 * is there only 1 philo?
 * call a quick simple func to make him quickly die (lil bro only got 1 fork)
 * alright, but the real deal?
 * 1. create all philo threads
 * 2. create an aux thread that will be checking up on our philos to see
 * whether or not there're any dead ones
 * 3. because creating threads takes some time, the simulation will desync
 * from the start. to avoid that, we need to sync everyone once we've created
 * everyone.
 * 4. join everyone, whatever that means... is this... the sixth house, house
 * dagoth, the tribe unmourned?...
 */
int	dinner_start_2(t_data *data)
{
	int	i;

	data->start_simulation = gettime(MILSEC);
	if (data->start_simulation == -1)
		return (1);
//	mtx_set_i(&(data->data_mtx), &(data->ready_to_start), 1); // TODO check without mtx_set but directly ? or is it ok
	data->ready_to_start = 1;
	i = -1;
	while (++i < data->philo_number)
	{
		if (thread_try(&(data->philos[i].thread_id), 0, 0, JOIN))
			return (1);
	}
	return (0);
}

int	dinner_start(t_data *data)
{
	int	i;

	if (data->meals_limit_number == 0)
		return (0);
	if (data->philo_number == 1)
		;// TODO
	else
	{
		i = -1;
		while (++i < data->philo_number)
		{
			if (thread_try(&data->philos[i].thread_id, dinner_sim,
					&data->philos[i], CREATE))
				return (1);
		}
	}
	if (dinner_start_2(data))
		return (1);
	// TODO
	return (0);
}
