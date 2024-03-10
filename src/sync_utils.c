/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/08 17:42:39 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	in src/set.c
t_get_i	mtx_get_i(t_mtx *mutex, int *val);

/*
 * that's called a spinlock
 */
int	wait_all_threads(t_data *data)
{
	t_get_i	cond;

	cond = mtx_get_i(&(data->data_mtx),	&(data->ready_to_start));
	if (cond.errc)
		return (1);
	while (!cond.val)
	{
		cond = mtx_get_i(&(data->data_mtx),	&(data->ready_to_start));
		if (cond.errc)
			return (1);
	}
	return (0);
}
