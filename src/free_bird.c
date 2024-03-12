/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bird.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:59 by akozin            #+#    #+#             */
/*   Updated: 2024/03/12 16:12:31 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

//	in src/safe_funcs.c
int	mutex_try(t_mtx *mutex, t_opcode opcode);

void	free_bird_yeah(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

/*
 * if destroys fail here lol it's gg
 */
void	clean(t_data *data)
{
	t_philo	*ph;
	int		i;

	i = -1;
	while (++i < data->philo_n)
	{
		ph = &(data->philos[i]);
		if (mutex_try(&(ph->ph_mtx), DESTROY))
			break ;
	}
	mutex_try(&(data->write_mtx), DESTROY);
	mutex_try(&(data->data_mtx), DESTROY);
	free(data->forks);
	free(data->philos);
}
