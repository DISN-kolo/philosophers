/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:40:05 by akozin            #+#    #+#             */
/*   Updated: 2024/03/07 15:57:31 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

//	in src/input_parser_utils.c
int		ft_nbrlen(int x);
char	*ft_itoa(int n);
int		ft_strncmp(char *s1, char *s2, size_t n);

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	maxint_passed_checker(char *guy)
{
	char	*strmaxint;

	strmaxint = ft_itoa(INT_MAX);
	return (ft_strncmp(strmaxint, guy, ft_nbrlen(INT_MAX)) < 0);
}

int	guy_checker(char *guy)
{
	int	j;

	j = 0;
	while (guy[j])
	{
		if (!ft_isdigit(guy[j]))
			return (1);
		if (j > ft_nbrlen(INT_MAX))
			return (1);
		else if (j == ft_nbrlen(INT_MAX))
		{
			if (maxint_passed_checker(guy))
				return (1);
		}
		j++;
	}
	return (0);
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
	if (argc == 5)
		data->meals_limit_number = -1;
	if (argv_checker(argc, argv))
		return (1);
	return (0);
}
