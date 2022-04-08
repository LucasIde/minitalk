/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:10 by lide              #+#    #+#             */
/*   Updated: 2022/04/08 17:53:03 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_file/minitalk_bonus.h"

void	d_to_b(unsigned char c, int pid)
{
	int	max;

	max = 128;
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

void	len(char *arg, int pid_s, int pid_c, int access)
{
	unsigned int	i;
	unsigned int	max;

	i = 0;
	max = 2147483648;
	if (access == 0)
		i = pid_c;
	else if (access == 1)
	{
		while (arg[i])
			i++;
	}
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

void	receive(int sig)
{
	if (sig == SIGUSR2)
	{
		write(1, "We received your message\n", 25);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	int					pid_s;
	unsigned int		i;
	struct sigaction	sa3;

	if (argc != 3)
		return (0);
	sa3.sa_handler = &receive;
	sa3.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa3, NULL);
	pid_s = ft_atoi(argv[1]);
	if (pid_s < 0)
	{
		write(2, "Wrong PID\n", 10);
		return (0);
	}
	len(argv[2], pid_s, getpid(), 0);
	len(argv[2], pid_s, getpid(), 1);
	i = -1;
	while (argv[2][++i])
		d_to_b(argv[2][i], pid_s);
	while (1)
		sleep(1);
	return (0);
}
