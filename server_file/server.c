/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:14 by lide              #+#    #+#             */
/*   Updated: 2022/04/01 20:32:26 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int in;

int	ft_exp(void)
{
	int len;
	int nb;

	len = in;
	nb = 1;
	while (len > 0)
	{
		nb *= 2;
		len--;
	}
	return (nb);
}

void	handle_SIGUSR1(int sig)
{
	static int	nb;
	char c;

	--in;
	if (sig == SIGUSR1)
		nb += 0;
	if (sig == SIGUSR2)
		nb +=ft_exp();
	if (in == 0)
	{
		c = nb;
		write(1, &c, 1);
		in = 7;
		nb = 0;
	}

}

int main(void)
{
	struct sigaction sa1;
	struct sigaction sa2;

	printf("%d\n", getpid());
	in = 7;
	sa1.sa_handler = &handle_SIGUSR1;
	sa1.sa_flags = 0;
	sa2.sa_handler = &handle_SIGUSR1;
	sa2.sa_flags = 0;

	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa1, NULL);
	while (1)
		sleep(1);
	return (0);
}
