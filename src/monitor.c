/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:40:23 by akozin            #+#    #+#             */
/*   Updated: 2024/03/12 14:01:49 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	in src/set.c
void	mtx_set_i(t_mtx *mutex, int *dest, int val);
int		mtx_get_i(t_mtx *mutex, int *val);
long	mtx_get_l(t_mtx *mutex, long *val);
int		sim_finished(t_data *data);
//	in src/sync_utils.c
int		all_th_run(t_mtx *mutex, int *threads, int philo_n);
//	in src/utils.c
long	gettime(t_timecode timecode);
//	in src/write.c
void	write_status(t_status status, t_philo *ph);

int	philo_died(t_philo *ph)
{
	long	elap;
	long	ttd;

	if (mtx_get_i(&(ph->ph_mtx), &(ph->full)))
		return (0);
	elap = gettime(MILSEC) - mtx_get_l(&(ph->ph_mtx), &(ph->last_meal_time));
	ttd = ph->data->time_to_die / 1e3;
	if (elap > ttd)
		return (1);
	return (0);
}

void	*monitor_f(void *d)
{
	t_data	*data;
	int		i;

	data = (t_data *)d;
	while (!all_th_run(&(data->data_mtx), &(data->th_run_n), data->philo_n))
		;
	while (!sim_finished(data))
	{
		i = -1;
		while (++i < data->philo_n && !sim_finished(data))
		{
			if (philo_died(&(data->philos[i])))
			{
				mtx_set_i(&(data->data_mtx), &(data->end_simulation), 1);
				write_status(DEAD, &(data->philos[i]));
			}
		}
	}
	return (0);
}
