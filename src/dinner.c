/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/11 15:03:58 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

//	in src/safe_funcs.c
int		thread_try(pthread_t *th, void *(*f)(void *), void *data,
			t_opcode opcode);
//	in src/set.c
void	mtx_set_i(t_mtx *mutex, int *dest, int val);
//	in src/sync_utils.c
void	wait_all_threads(t_data *data);

void	*dinner_sim(void *d)
{
	t_philo	*ph;

	ph = (t_philo *)d;
	if (wait_all_threads(ph->data))
	{
		printf("wait_all_threads encountered an error.\n"
			"frankly, i have no idea what to do!\n");
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
	data->start_simulation = gettime(MILSEC);
	if (data->start_simulation == -1)
		return (1);
	mtx_set_i(&(data->data_mtx), &(data->ready_to_start), 1);
	i = -1;
	while (++i < data->philo_number)
	{
		if (thread_try(&(data->philos[i].thread_id), 0, 0, JOIN))
			return (1);
	}
	// TODO
	return (0);
}
