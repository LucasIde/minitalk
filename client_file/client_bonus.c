/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:10 by lide              #+#    #+#             */
/*   Updated: 2022/04/11 17:50:26 by lide             ###   ########.fr       */
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
		exit(0);
	}
}

int	write_error(int error, int argc)
{
	if (error == 0 && argc < 3)
		write(2, "Too few arguments", 17);
	else if (error == 0 && argc > 3)
		write(2, "Too many arguments", 18);
	if (error == 1)
		write(2, "Pid can't have letter", 21);
	return (0);
}

int	main(int argc, char **argv)
{
	int					pid_s;
	unsigned int		i;
	struct sigaction	sa3;

	if (argc != 3)
		return (write_error(0, argc));
	sa3.sa_handler = &receive;
	sa3.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa3, NULL);
	pid_s = ft_atoi(argv[1]);
	if (pid_s < 0)
		return (write_error(1, argc));
	len(argv[2], pid_s, getpid(), 0);
	len(argv[2], pid_s, getpid(), 1);
	i = -1;
	while (argv[2][++i])
		d_to_b(argv[2][i], pid_s);
	sleep(3);
	write(2, "Message send to wrong Pid", 9);
	return (1);
}
