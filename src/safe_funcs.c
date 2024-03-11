/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:54:13 by akozin            #+#    #+#             */
/*   Updated: 2024/03/11 14:46:55 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

/*
 * alledgedly, saves lines.
 */
int	p_malloc_try(size_t bytes, t_philo **what)
{
	(*what) = malloc(bytes);
	if (!(*what))
		return (1);
	return (0);
}

int	f_malloc_try(size_t bytes, t_fork **what)
{
	(*what) = malloc(bytes);
	if (!(*what))
		return (1);
	return (0);
}

/*
 * safening of mutex ops:
 * init
 * destroy
 *
 * we don't need to safe-ify:
 * lock
 * unlock
 *
 * if we get an error THERE, we done f-d up big time somewhere. no salvation.
 */
int	mutex_try(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == INIT)
		return (pthread_mutex_init(mutex, 0));
	if (opcode == DESTROY)
		return (pthread_mutex_destroy(mutex));
	return (1);
}

/*
 * same for threads:
 * create
 * join
 * destroy
 */
int	thread_try(pthread_t *th, void *(*f)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		return (pthread_create(th, 0, f, data));
	if (opcode == JOIN)
		return (pthread_join(*th, 0));
	if (opcode == DETACH)
		return (pthread_detach(*th));
	return (1);
}
