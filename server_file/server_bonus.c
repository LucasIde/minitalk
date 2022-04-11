/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:14:14 by lide              #+#    #+#             */
/*   Updated: 2022/04/11 17:24:35 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_file/minitalk_bonus.h"

void	first_signal(int sig, unsigned int *len, int *first_ct, char **str)
{
	int	tmp;

	if (*first_ct > 32)
		tmp = *first_ct - 32;
	else
		tmp = *first_ct;
	if (*first_ct > 0)
	{
		(*first_ct)--;
		if (sig == SIGUSR2)
			*len += ft_exp(tmp - 1);
	}
	if (*first_ct == 0)
	{
		*str = (char *)malloc(sizeof(char) * (*len));
		if (!*str)
		{
			write(2, "Malloc Error", 12);
			exit(1);
		}
		(*first_ct)--;
	}
}

void	second_signal(int sig, unsigned int *len, int *first_ct, char **str)
{
	unsigned char		letter;
	static int			letter_ct = 8;
	static unsigned int	nb;
	static unsigned int	i;

	--letter_ct;
	if (sig == SIGUSR2)
		nb += ft_exp(letter_ct);
	if (letter_ct == 0)
	{
		letter = nb;
		(*str)[i] = letter;
		letter_ct = 8;
		nb = 0;
		if (++i == *len)
		{
			write(1, *str, *len);
			free(*str);
			*first_ct = 64;
			*len = 0;
			i = 0;
		}
	}
}

void	handle_signal(int sig)
{
	static char			*str;
	static int			first_ct = 64;
	static int			pid_c;
	static unsigned int	len;

	if (first_ct >= 33)
	{
		first_signal(sig, &len, &first_ct, &str);
		if (first_ct == 32)
		{
			pid_c = len;
			len = 0;
		}
	}
	else if (first_ct >= 0 && first_ct <= 32)
		first_signal(sig, &len, &first_ct, &str);
	else if (first_ct == -1)
		second_signal(sig, &len, &first_ct, &str);
	if (first_ct == 64)
		kill(pid_c, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa1;
	int					verif;

	verif = ft_printnbr((int)getpid());
	if (verif == -1)
	{
		write(2, "Error itoa", 10);
		return (0);
	}
	sa1.sa_handler = &handle_signal;
	sa1.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa1, NULL);
	while (1)
	{
		sleep(1);
	}
	return (0);
}
