/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:04:26 by akozin            #+#    #+#             */
/*   Updated: 2024/03/07 13:59:04 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s <N of philos> <die T> <eat T> <eep T> [N of meals]\n",
			argv[0]);
		return (1);
	}
	return (0);
}
