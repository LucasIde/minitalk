/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:15:15 by lide              #+#    #+#             */
/*   Updated: 2022/04/06 16:24:50 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>


# include <stdio.h>

char			*ft_itoa2(long n2, int nb);
char			*ft_itoa(int n);
long			ft_atoi(const char *str);
unsigned int	ft_exp(int in);

#endif
