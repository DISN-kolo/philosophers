/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/12 13:11:07 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	in src/set.c
int	mtx_get_i(t_mtx *mutex, int *val);

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
