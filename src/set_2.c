/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:53:50 by akozin            #+#    #+#             */
/*   Updated: 2024/03/12 12:56:07 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mtx_inc_i(t_mtx *mutex, int *val)
{
	pthread_mutex_lock(mutex);
	*val = *val + 1;
	pthread_mutex_unlock(mutex);
}
