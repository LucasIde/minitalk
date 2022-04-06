/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:10 by lide              #+#    #+#             */
/*   Updated: 2022/04/06 18:00:54 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

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
	if (sig == 31)
	{
		write(1, "We received your message", 24);
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
	pid_s = ft_atoi(argv[1]);
	if (pid_s < 0)
	{
		write(1, "WRONG PID", 9);
		return (0);
	}
	printf("%d\n", getpid());
	len(argv[2], pid_s, getpid(), 0);
	len(argv[2], pid_s, getpid(), 1);
	i = -1;
	while (argv[2][++i])
		d_to_b(argv[2][i], pid_s);
	sa3.sa_handler = &receive;
	// sa3.sa_flags = 0;
	sigaction(SIGUSR2, &sa3, NULL);
	while (1)
		sleep(1);
	return (0);
}
