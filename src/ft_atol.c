/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:19:19 by akozin            #+#    #+#             */
/*   Updated: 2024/03/08 12:24:14 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long	ft_isspace(char x)
{
	return (x == '\t' || x == '\n' || x == '\v' || x == '\f' || x == '\r'
		|| x == ' ');
}

static long	ft_isn(char x)
{
	return (x >= '0' && x <= '9');
}

static long	ft_issign(char x)
{
	return (x == '-' || x == '+');
}

static long	twenty_fiver(long *sixn, char *str)
{
	while (str[sixn[1]])
	{
		if (ft_isspace(str[sixn[1]]) && (sixn[2] <= 0))
			sixn[2] = 0;
		else if (ft_issign(str[sixn[1]]) && (sixn[2] <= 1))
		{
			sixn[2] = 2;
			sixn[0] = 1 - (str[sixn[1]] == '-') * 2;
		}
		else if (ft_isn(str[sixn[1]]) && (sixn[2] <= 2))
		{
			sixn[2] = 2;
			sixn[3] = sixn[3] * 10 + (str[sixn[1]] - '0');
		}
		else
			break ;
		sixn[1]++;
	}
	return (sixn[3] * sixn[0]);
}

/* x is state. -1 is starting, 0 is spaces, 1 is signs, 2 is numbers. */
/* sixn is our magic array containing s, i, x, n */
long	ft_atol(char *str)
{
	long	sixn[4];

	sixn[0] = 1;
	sixn[1] = 0;
	sixn[2] = -1;
	sixn[3] = 0;
	return (twenty_fiver(sixn, str));
}
