/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:08:08 by akozin            #+#    #+#             */
/*   Updated: 2024/03/07 16:19:06 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <stddef.h>

/*
 * ripped from libft, lol
 * we're not allowed to use the whole package (bs of the printf? thread safety?
 * but nothing prevents us from copying random stuff from it y'know. tee-hee
 */
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\f' || c == '\v');
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int		p;
	size_t	c;

	if (n == 0)
		return (0);
	p = 0;
	c = 0;
	while ((unsigned char)s1[p] != 0 && (unsigned char)s2[p] != 0 && c < n)
	{
		if ((unsigned char)s1[p] != (unsigned char)s2[p])
			return (free(s1), (unsigned char)s1[p] - (unsigned char)s2[p]);
		p++;
		c++;
	}
	if ((unsigned char)s1[p] != (unsigned char)s2[p] && c < n)
		return (free(s1), (unsigned char)s1[p] - (unsigned char)s2[p]);
	free(s1);
	return (0);
}

static int	ft_p(int i, int p)
{
	int	ii;

	ii = i;
	if (!p)
		return (1);
	while (--p)
		i *= ii;
	return (i);
}

int	ft_nbrlen(int x)
{
	int	count;

	count = 0;
	if (!x)
		return (1);
	while (x)
	{
		x /= 10;
		count++;
	}
	return (count);
}

/*
 * r = return array (string)
 * dc = digit counter. it is the index for running through r.
 * ds = digit "sum" (idk why i named it like that but it's the TOTAL
 * digit count at the start. it's getting less in orded to go through
 * the number's digits in reverse (from the biggest to the smallest)
 * because we're writing from left to right.
 */
char	*ft_itoa(int n)
{
	char	*r;
	int		ds;
	int		dc;

	r = (char *)malloc(ft_nbrlen(n) + 1);
	if (!r)
		return (r);
	dc = 0;
	ds = ft_nbrlen(n);
	if (ds == ft_nbrlen(INT_MAX))
		r[dc++] = n / ft_p(10, --ds) + '0';
	while (dc < (ft_nbrlen(n) + (n < 0)))
	{
		r[dc++] = (n / ft_p(10, ds - 1)) - 10 * (n / ft_p(10, ds)) + '0';
		ds--;
	}
	r[dc] = 0;
	return (r);
}
