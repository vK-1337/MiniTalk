/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:40:25 by vda-conc          #+#    #+#             */
/*   Updated: 2023/12/09 15:59:50 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_bin_to_char(int signum, int *c)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c = (*c << 1) | 0;
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	c;
	static int	i;
	pid_t		client_pid;

	(void)context;
	client_pid = info->si_pid;
	ft_bin_to_char(signum, &c);
	if (++i == 8)
	{
		i = 0;
		if (c == '\0')
		{
			write(1, "\n", 1);
			client_pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	server_action;
	char				*pid;

	server_action.sa_flags = SA_SIGINFO;
	server_action.sa_sigaction = sig_handler;
	sigemptyset(&server_action.sa_mask);
	pid = ft_itoa(getpid());
	write(1, "\nWelcome to the server !\n", 26);
	write(1, "\nYou can find my PID below\n", 28);
	write(1, "\nSERVER PID = ", 15);
	write(1, pid, 7);
	write(1, "\n\nWaiting to receive message...\n\n", 34);
	write(1, "---------------------------------------------------\n\n", 54);
	sigaction(SIGUSR1, &server_action, NULL);
	sigaction(SIGUSR2, &server_action, NULL);
	free(pid);
	while (1)
		pause();
	return (0);
}
