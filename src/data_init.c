/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:53:05 by akozin            #+#    #+#             */
/*   Updated: 2024/03/12 13:12:16 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdlib.h"

//	in src/safe_funcs.c
int	p_malloc_try(size_t bytes, t_philo **what);
int	f_malloc_try(size_t bytes, t_fork **what);
int	mutex_try(t_mtx *mutex, t_opcode opcode);

/*
 * odd-even assignment of forks.
 * the even people will take their first fork from the right
 * the odd people will take their first fork from the left
 */
void	assign_forks(t_philo *ph, t_fork *forks, int pos)
{
	int	ph_n;

	ph_n = ph->data->philo_n;
	if (!(ph->id % 2))
	{
		ph->first_fork = &forks[pos];
		ph->second_fork = &forks[(pos + 1) % ph_n];
	}
	else
	{
		ph->first_fork = &forks[(pos + 1) % ph_n];
		ph->second_fork = &forks[pos];
	}
}

int	philo_init(t_data *data)
{
	int		i;
	t_philo	*ph;

	i = 0;
	while (i < data->philo_n)
	{
		ph = &(data->philos[i]);
		ph->id = i + 1;
		ph->full = 0;
		ph->meals_counter = 0;
		ph->data = data;
		if (mutex_try(&data->philos[i].ph_mtx, INIT))
			return (1);
		assign_forks(ph, data->forks, i);
		i++;
	}
	return (0);
}

int	data_init(t_data *data)
{
	int	i;

	data->end_simulation = 0;
	data->ready_to_start = 0;
	data->th_run_n = 0;
	if (p_malloc_try(data->philo_n * sizeof (t_philo), &(data->philos)))
		return (1);
	if (f_malloc_try(data->philo_n * sizeof (t_fork), &(data->forks)))
		return (1);
	if (mutex_try(&(data->data_mtx), INIT))
		return (1);
	if (mutex_try(&(data->write_mtx), INIT))
		return (1);
	i = 0;
	while (i < data->philo_n)
	{
		if (mutex_try(&(data->forks[i].fork), INIT))
			return (1);
		data->forks[i].fork_id = i;
		i++;
	}
	if (philo_init(data))
		return (1);
	return (0);
}
