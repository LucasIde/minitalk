/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:10 by lide              #+#    #+#             */
/*   Updated: 2022/04/11 22:21:58 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_file/minitalk.h"

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

int	write_error(int error, int argc)
{
	if (error == 0 && argc < 3)
		write(2, "Too few arguments", 17);
	else if (error == 0 && argc > 3)
		write(2, "Too many arguments", 18);
	else if (error == 1)
		write(2, "Pid can't have letter", 21);
	else if (error == 2)
		write(2, "Unknown character\n", 18);
	return (0);
}

int	main(int argc, char **argv)
{
	int					pid_s;
	unsigned int		i;

	if (argc != 3)
		return (write_error(0, argc));
	pid_s = ft_atoi(argv[1]);
	if (pid_s < 0)
		return (write_error(1, argc));
	i = -1;
	while (argv[2][++i])
	{
		if (argv[2][i] < 0 || argv[2][i] > 127)
			return (write_error(2, argc));
	}
	len(argv[2], pid_s);
	i = -1;
	while (argv[2][++i])
		d_to_b(argv[2][i], pid_s);
	return (1);
}
