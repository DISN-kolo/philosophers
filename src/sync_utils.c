/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/12 17:09:21 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	in src/set.c
int		mtx_get_i(t_mtx *mutex, int *val);
//	in src/dinner.c
void	think(t_philo *ph, int before_sim);
//	in src/utils.c
void	pusleep(long usec, t_data *data);

/*
 * that's called a spinlock
 */
void	wait_all_threads(t_data *data)
{
	while (!mtx_get_i(&(data->data_mtx), &(data->ready_to_start)))
		;
}

/*
 * and that's for the monitor. it's called busy waiting, ust like ^
 */
int	all_th_run(t_mtx *mutex, int *threads, int philo_n)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex);
	if (*threads == philo_n)
		ret = 1;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/*
 * even n = all seems to run fair, but we still gonna delay some things
 * to be sure. but in general everyone will be alternating in a checker
 * pattern, so all's good
 *
 * odd n = system can be fair, but also easily can fail. we need to
 * re-think our thinking
 */
void	desync(t_philo *ph)
{
	if (ph->data->philo_n % 2 == 0)
	{
		if (ph->id % 2 == 0)
			pusleep(3e4, ph->data);
	}
	else
	{
		if (ph->id % 2 == 0)
			think(ph, 1);
	}
}
