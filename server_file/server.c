/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:14 by lide              #+#    #+#             */
/*   Updated: 2022/04/06 17:56:46 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

char	*g_str;

void	first_signal(int sig, unsigned int *len, int *gl)
{
	int	p;

	if (*gl > 32)
		p = *gl - 32;
	else
		p = *gl;
	if (*gl > 0)
	{
		(*gl)--;
		if (sig == SIGUSR2)
			*len += ft_exp(p - 1);
	}
	if (*gl == 0)
	{
		g_str = (char *)malloc(sizeof(char) * (*len));
		(*gl)--;
	}
}

void	second_signal(int sig, unsigned int *len, int *gl, int pid_c)
{
	char				c;
	static int			in = 7;
	static unsigned int			nb;
	static unsigned int	i;

	--in;
	if (sig == SIGUSR2)
		nb += ft_exp(in);
	if (in == 0)
	{
		c = nb;
		g_str[i] = c;
		in = 7;
		nb = 0;
		if (++i == *len)
		{
			write(1, g_str, *len);
			free(g_str);
			printf("%d\n", pid_c);
			// kill(pid_c, SIGUSR2);
			*gl = 64;
			*len = 0;
			i = 0;
		}
	}
}

void	handle_signal(int sig)
{
	static int			gl = 64;
	static unsigned int	len;
	static int			pid_c;

	if (gl >= 33)
	{
		first_signal(sig, &len, &gl);
		if (gl == 32)
		{
			pid_c = len;
			len = 0;
		}
	}
	else if (gl >= 0 && gl <= 32)
		first_signal(sig, &len, &gl);
	else if (gl == -1)
		second_signal(sig, &len, &gl, pid_c);
}

int	main(void)
{
	struct sigaction	sa1;

	printf("%d\n", getpid());
	sa1.sa_handler = &handle_signal;
	sa1.sa_flags = 0;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa1, NULL);
	while (1)
		sleep(1);
	return (0);
}
