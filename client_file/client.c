/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:10 by lide              #+#    #+#             */
/*   Updated: 2022/04/05 18:19:29 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static char	*ft_itoa2(long n2, int nb)
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

void	d_to_b(char c, int pid)
{
	int	max;

	max = 64;
	while (max > 0)
	{
		if (c >= max)
		{
			kill(pid, SIGUSR2);
			c -= max;
		}
		else
			kill(pid, SIGUSR1);
		max /= 2;
		usleep(50);
	}
}

void	len(char *arg, int pid)
{
	int	i;
	int	max;

	i = 0;
	max = 1073741824;
	while (arg[i])
		i++;
	while (max > 0)
	{
		if (i >= max)
		{
			kill(pid, SIGUSR2);
			i -= max;
		}
		else
			kill(pid, SIGUSR1);
		max /= 2;
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	int		pid_s;
	int		i;

	if (argc != 3)
		return (0);
	pid_s = ft_atoi(argv[1]);
	if (pid_s < 0)
	{
		write(1, "WRONG PID", 9);
		return (0);
	}
	len(argv[2], pid_s);
	i = -1;
	while (argv[2][++i])
		d_to_b(argv[2][i], pid_s);
	return (0);
}
