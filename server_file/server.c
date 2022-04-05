/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:14 by lide              #+#    #+#             */
/*   Updated: 2022/04/05 18:59:25 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

char	*str;

int	ft_exp(int in)
{
	int	nb;

	nb = 1;
	while (in > 0)
	{
		nb *= 2;
		in--;
	}
	return (nb);
}

void	handle_sigusr1(int sig)
{
	static int	nb;
	static int	in = 7;
	static int	gl = 31;
	static int	len;
	static int	i;
	char		c;

	if (gl > 0)
	{
		gl--;
		if (sig == SIGUSR1)
			len += 0;
		if (sig == SIGUSR2)
			len += ft_exp(gl);
	}
	else if (gl == 0)
	{
		str = (char *)malloc(sizeof(char) * len);
		gl--;
	}
	if (gl == -1)
	{
		--in;
		if (sig == SIGUSR1)
			nb += 0;
		if (sig == SIGUSR2)
			nb += ft_exp(in);
		if (in == 0)
		{
			c = nb;
			str[i] = c;
			in = 7;
			nb = 0;
			i++;
			if (i == len)
			{
				write(1, str, len);
				free(str);
				gl = 31;
			}
		}
	}
}

int	main(void)
{
	struct sigaction	sa1;

	printf("%d\n", getpid());
	sa1.sa_handler = &handle_sigusr1;
	sa1.sa_flags = 0;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa1, NULL);
	while (1)
		sleep(1);
	return (0);
}
