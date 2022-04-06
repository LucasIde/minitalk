/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:55:38 by lide              #+#    #+#             */
/*   Updated: 2022/04/06 16:22:22 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

char	*ft_itoa2(long n2, int nb)
{
	int		i;
	char	*a;

	i = 0;
	if (n2 < 0)
		return (NULL);
	a = (char *)malloc(sizeof(char) * (nb + 1));
	if (!a)
		return (NULL);
	a[nb] = 0;
	while (nb > i)
	{
		a[nb - 1] = (n2 % 10) + '0';
		n2 /= 10;
		nb--;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	int		nb;
	long	n2;

	n2 = (long)n;
	nb = 0;
	while (n2 > 0)
	{
		n2 /= 10;
		nb++;
	}
	return (ft_itoa2((long)n, nb));
}

long	ft_atoi(const char *str)
{
	long	j;
	int		i;

	j = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		j *= 10;
		j += str[i] - '0';
		if (j > 2147483648)
			return (-1);
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	return (j);
}

unsigned int	ft_exp(int in)
{
	unsigned int	nb;

	nb = 1;
	while (in > 0)
	{
		nb *= 2;
		in--;
	}
	return (nb);
}
