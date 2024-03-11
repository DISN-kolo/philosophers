/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/11 14:49:19 by akozin           ###   ########.fr       */
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
	{
		;
	}
}
