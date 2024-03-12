/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:01:54 by akozin            #+#    #+#             */
/*   Updated: 2024/03/12 13:51:51 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

//	in src/set.c
int		sim_finished(t_data *data);
void	mtx_set_l(t_mtx *mutex, long *dest, long val);
int		sim_finished(t_data *data);
//	in src/set2.c
void	mtx_inc_i(t_mtx *mutex, int *val);
//	in src/sync_utils.c
void	wait_all_threads(t_data *data);
//	in src/write.c
void	write_status(t_status status, t_philo *ph);

/*
 * because theoretically we can get t = 0 returns, an error shall be indicated
 * by returning -1
 */
long	gettime(t_timecode timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		return (-1);
	if (timecode == SEC)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (timecode == MILSEC)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (timecode == MICSEC)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else
		return (-1);
}

void	pusleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICSEC);
	while (gettime(MICSEC) - start < usec)
	{
		if (sim_finished(data))
			break ;
		elapsed = gettime(MICSEC) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (gettime(MICSEC) - start < usec)
				;
		}
	}
}

void	*alone(void *d)
{
	t_philo	*ph;

	ph = (t_philo *)d;
	wait_all_threads(ph->data);
	mtx_set_l(&(ph->data->data_mtx), &(ph->last_meal_time), gettime(MILSEC));
	mtx_inc_i(&(ph->data->data_mtx), &(ph->data->th_run_n));
	write_status(TAKE_F_FORK, ph);
	while (!sim_finished(ph->data))
		usleep(200);
	return (0);
}
