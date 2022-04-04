/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:14 by lide              #+#    #+#             */
/*   Updated: 2022/04/04 19:27:11 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int gl;

int	ft_exp(int in)
{
	int	len;
	int	nb;

	len = in;
	nb = 1;
	while (len > 0)
	{
		nb *= 2;
		len--;
	}
	return (nb);
}

void	handle_sigusr1(int sig)
{
	static int	nb;
	static int	in = 9;
	char		c;

	--in;
	if (in > 6)//envoi deux signaux pour savoir dans quel cas je suis
	{
		if (sig == SIGUSR1)
			gl += 0;
		if (sig == SIGUSR2)
			gl += 1;
	}
	if (in <= 6 && in > 0)
	{
		if (sig == SIGUSR1)
			nb += 0;
		if (sig == SIGUSR2)
			nb += ft_exp(in);
	}
	if (gl == 1)
	{
		if (in == 0)
		{
			c = nb;
			write(1, &c, 1);
			in = 9;
			nb = 0;
			gl = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	sa1;

	printf("%d\n", getpid());
	gl = 0;
	sa1.sa_handler = &handle_sigusr1;
	sa1.sa_flags = 0;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa1, NULL);
	while (1)
		sleep(1);
	return (0);
}
