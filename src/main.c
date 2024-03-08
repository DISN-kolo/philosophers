/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:04:26 by akozin            #+#    #+#             */
/*   Updated: 2024/03/08 12:58:38 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

//	in src/input_parser.c
int	input_parser(t_data *data, int argc, char **argv);
//	in src/data_init.c
int	data_init(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s <N of philos> <die T> <eat T> <eep T> [N of meals]\n",
			argv[0]);
		return (1);
	}
	if (input_parser(&data, argc, argv))
		return (1);
	if (data_init(&data))
		return (2);
//	dinner_start(&data);
	return (0);
}
