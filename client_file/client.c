/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:10 by lide              #+#    #+#             */
/*   Updated: 2022/04/01 20:32:25 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	atoi2(const char *str, int i, int x)
{
	long	j;
	long	tmp;

	j = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = j;
		j *= 10;
		j += str[i] - '0';
		if (tmp > j)
		{
			if (x == -1)
				return (0);
			if (x == 1)
				return (-1);
		}
		i++;
	}
	return (j * x);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		x;

	i = 0;
	x = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			x = -1;
		i++;
	}
	return (atoi2(str, i, x));
}

void	d_to_b(char c, int pid)
{
	int max;

	max = 64;
	while (max > 0)
	{
		if(c >= max)
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

int main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = -1;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
	while (argv[2][++i])
		d_to_b(argv[2][i], pid);
	}
	return (0);
}
