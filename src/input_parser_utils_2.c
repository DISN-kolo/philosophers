/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:36:13 by akozin            #+#    #+#             */
/*   Updated: 2024/03/07 17:06:43 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>

//	in src/input_parser_utils.c
int		ft_nbrlen(int x);
char	*ft_itoa(int n);
int		ft_strncmp(char *s1, char *s2, size_t n);

int	maxint_passed_checker(char *guy)
{
	char	*strmaxint;

	strmaxint = ft_itoa(INT_MAX);
	return (ft_strncmp(strmaxint, guy, ft_nbrlen(INT_MAX)) < 0);
}
