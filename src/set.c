/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:53:05 by akozin            #+#    #+#             */
/*   Updated: 2024/03/08 17:43:32 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	in src/safe_funcs.c
int	mutex_try(t_mtx *mutex, t_opcode opcode)

int	mtx_set_i(t_mtx *mutex, int *dest, int val)
{
	if (mutex_try(mutex, LOCK))
		return (1);
	*dest = val;
	if (mutex_try(mutex, UNLOCK))
		return (1);
	return (0);
}

int	mtx_set_l(t_mtx *mutex, long *dest, long val)
{
	if (mutex_try(mutex, LOCK))
		return (1);
	*dest = val;
	if (mutex_try(mutex, UNLOCK))
		return (1);
	return (0);
}

t_get_i	mtx_get_i(t_mtx *mutex, int *val)
{
	t_get_i	ret;

	if (mutex_try(mutex, LOCK))
	{
		ret.errc = 1;
		return (ret);
	}
	ret.val = *val;
	if (mutex_try(mutex, UNLOCK))
	{
		ret.errc = 1;
		return (ret);
	}
	ret.errc = 0;
	return (ret);
}

t_get_l	mtx_get_l(t_mtx *mutex, long *val)
{
	t_get_l	ret;

	if (mutex_try(mutex, LOCK))
	{
		ret.errc = 1;
		return (ret);
	}
	ret.val = *val;
	if (mutex_try(mutex, UNLOCK))
	{
		ret.errc = 1;
		return (ret);
	}
	ret.errc = 0;
	return (ret);
}

t_get_i	sim_finished(t_data *data)
{
	return (mtx_get_i(&(data->data_mtx), &(data->end_simulation)));
}
