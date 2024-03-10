/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/08 17:42:39 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	in src/safe_funcs.c
int	thread_try(pthread_t *th, void *(*f)(void *), void *data, t_opcode opcode);

void	*dinner_sim(void *d)
{
	t_philo *ph;

	ph = (t_philo *)d;
	wait_all_threads(ph->data); // TODO
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
int	dinner_start(t_data *data)
{
	int	i;

	if (data->meals_limit_number == 0)
		return (0);
	if (data->philo_number == 1)
		;// TODO
	else
	{
		i = 0;
		while (i < data->philo_number)
		{
			if (thread_try(&data->philos[i].thread_id, dinner_sim,
					&data->philos[i], CREATE))
				return (1);
			i++;
		}
	}
	
	return (0);
}