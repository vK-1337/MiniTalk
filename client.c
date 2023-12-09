/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:40:23 by vda-conc          #+#    #+#             */
/*   Updated: 2023/12/09 16:02:13 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_receiver;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	g_receiver = 1;
}

int	ft_char_to_bin(char c, int pid)
{
	int	itr;
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		itr = 0;
		if ((c >> bit_index) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_receiver == 0)
		{
			if (itr == 50)
			{
				exit(0);
			}
			itr++;
			usleep(100);
		}
		g_receiver = 0;
		bit_index--;
	}
	return (0);
}

int	main(int ac, char **av)
{
	struct sigaction	client_action;
	int					server_pid;
	int					byte_index;

	client_action.sa_flags = SA_SIGINFO;
	client_action.sa_sigaction = sig_handler;
	sigemptyset(&client_action.sa_mask);
	if (ac != 3 || !av[1] || !av[2])
	{
		write(1, "Usage: ./client <server_pid> <string>\n", 39);
		return (0);
	}
	server_pid = atoi(av[1]);
	sigaction(SIGUSR2, &client_action, NULL);
	byte_index = 0;
	while (av[2][byte_index] != '\0')
	{
		ft_char_to_bin(av[2][byte_index], server_pid);
		byte_index++;
	}
	ft_char_to_bin('\0', server_pid);
	return (0);
}
