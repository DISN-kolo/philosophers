/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:50:55 by akozin            #+#    #+#             */
/*   Updated: 2024/03/12 18:06:10 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

//	in src/set.c
int		sim_finished(t_data *data);
//	in src/utils.c
long	gettime(t_timecode timecode);

/*
 * timestamp_ms X has taken a fork
 * timestamp_ms X is eating
 * timestamp_ms X is sleeping
 * timestamp_ms X is thinking
 * timestamp_ms X died
 */
void	write_status(t_status status, t_philo *ph)
{
	long	elapsed;

	if (ph->full)
		return ;
	pthread_mutex_lock(&ph->data->write_mtx);
	elapsed = gettime(MILSEC) - ph->data->start_simulation;
	if ((status == TAKE_F_FORK || status == TAKE_S_FORK)
		&& !sim_finished(ph->data))
		printf("%ld %d has taken a fork\n", elapsed, ph->id);
	else if (status == EATING && !sim_finished(ph->data))
		printf("%ld %d is eating\n", elapsed, ph->id);
	else if (status == SLEEPING && !sim_finished(ph->data))
		printf("%ld %d is sleeping\n", elapsed, ph->id);
	else if (status == THINKING && !sim_finished(ph->data))
		printf("%ld %d is thinking\n", elapsed, ph->id);
	else if (status == DEAD)
		printf("%ld %d died\n", elapsed, ph->id);
	pthread_mutex_unlock(&ph->data->write_mtx);
}
