/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:10 by lide              #+#    #+#             */
/*   Updated: 2022/04/08 18:40:00 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_file/minitalk.h"

void	d_to_b(unsigned char c, int pid)
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

void	len(char *arg, int pid_s)
{
	unsigned int	i;
	unsigned int	max;

	i = 0;
	max = 2147483648;
	while (arg[i])
		i++;
	while (max > 0)
	{
		if (i >= max)
		{
			kill(pid_s, SIGUSR2);
			i -= max;
		}
		else
			kill(pid_s, SIGUSR1);
		max /= 2;
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	int					pid_s;
	unsigned int		i;

	if (argc != 3)
		return (0);
	pid_s = ft_atoi(argv[1]);
	if (pid_s < 0)
	{
		write(2, "Wrong PID\n", 10);
		return (0);
	}
	i = -1;
	while (argv[2][++i])
	{
		if (argv[2][i] < 0 || argv[2][i] > 127)
		{
			write(2, "Unknow character\n", 17);
			return (0);
		}
	}
	len(argv[2], pid_s);
	i = -1;
	while (argv[2][++i])
		d_to_b(argv[2][i], pid_s);
	return (0);
}
