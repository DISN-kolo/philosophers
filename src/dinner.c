/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/11 17:01:22 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

//	in src/safe_funcs.c
int		thread_try(pthread_t *th, void *(*f)(void *), void *data,
			t_opcode opcode);
//	in src/set.c
void	mtx_set_i(t_mtx *mutex, int *dest, int val);
int		sim_finished(t_data *data);
//	in src/sync_utils.c
void	wait_all_threads(t_data *data);
//	in src/utils.c
void	pusleep(long usec, t_data *data);
//	in src/write.c
void	write_status(t_status status, t_philo *ph);

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
		eat(ph); // TODO
		write_status(SLEEPING, ph);
		pusleep(ph->data->time_to_sleep, ph->data);
		think(ph); // TODO
	}
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
	mtx_set_i(&(data->data_mtx), &(data->ready_to_start), 1); // TODO check without mtx_set but directly
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
