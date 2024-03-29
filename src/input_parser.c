/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:40:05 by akozin            #+#    #+#             */
/*   Updated: 2024/03/12 13:11:26 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

//	in src/input_parser_utils.c
int		ft_nbrlen(int x);
int		ft_isspace(char c);
//	in src/input_parser_utils_2.c
int		maxint_passed_checker(char *guy);
//	in src/ft_atoi.c
long	ft_atol(char *str);

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	guy_checker_internal(char *guy, int j)
{
	int	count;

	count = 0;
	while (guy[j] && ft_isdigit(guy[j]))
	{
		if (count >= ft_nbrlen(INT_MAX))
			return (1);
		else if (count == ft_nbrlen(INT_MAX) - 1)
		{
			if (maxint_passed_checker(guy + j - count))
				return (1);
		}
		j++;
		count++;
	}
	while (guy[j])
	{
		if (!ft_isspace(guy[j]))
			return (1);
		j++;
	}
	return (0);
}

int	guy_checker(char *guy)
{
	int	j;

	j = 0;
	while (ft_isspace(guy[j]))
		j++;
	if (!guy[j])
		return (1);
	if (guy[j] != '+' && !ft_isdigit(guy[j]))
		return (1);
	else if (guy[j] == '+' && !ft_isdigit(guy[j + 1]))
		return (1);
	j += (guy[j] == '+');
	while (guy[j] == '0')
		j++;
	return (guy_checker_internal(guy, j));
}

int	argv_checker(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (guy_checker(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	input_parser(t_data *data, int argc, char **argv)
{
	if (argv_checker(argc, argv))
		return (1);
	if (argc == 5)
		data->meals_limit_number = -1;
	else
		data->meals_limit_number = ft_atol(argv[5]);
	data->philo_n = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	return (0);
}
