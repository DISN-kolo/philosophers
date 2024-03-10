/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/08 17:42:39 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

/*
 * because theoretically we can get t = 0 returns, an error shall be indicated
 * by returning -1
 */
long	gettime(t_timecode timecode)
{
	struct timeval	tv;

	if (!gettimeofday(&tv, 0))
		return (-1);
	if (time_code == SEC)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (time_code == MILSEC)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (time_code == MIRLSEC)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else
		return (-1);
}
