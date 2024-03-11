/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:53:05 by akozin            #+#    #+#             */
/*   Updated: 2024/03/11 14:41:02 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mtx_set_i(t_mtx *mutex, int *dest, int val)
{
	pthread_mutex_lock(mutex);
	*dest = val;
	pthread_mutex_unlock(mutex);
}

void	mtx_set_l(t_mtx *mutex, long *dest, long val)
{
	pthread_mutex_lock(mutex);
	*dest = val;
	pthread_mutex_unlock(mutex);
}

int	mtx_get_i(t_mtx *mutex, int *val)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

long	mtx_get_l(t_mtx *mutex, long *val)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

t_get_i	sim_finished(t_data *data)
{
	return (mtx_get_i(&(data->data_mtx), &(data->end_simulation)));
}
