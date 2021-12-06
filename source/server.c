/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:57:36 by soumanso          #+#    #+#             */
/*   Updated: 2021/12/06 19:32:55 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* Accumulate bits received from the client. Once 8 bits have been
 received, we print the resulting byte and reset to 0.
 Once 8 zero bits have been received (byte = 0), we print a newline
 and consider that the communication with the client has ended. */
static void	receive_bit(pid_t client_pid, t_u8 bit)
{
	static pid_t	current_client;
	static t_u8		final_byte;
	static t_int	bit_index;

	if (current_client != 0 && current_client != client_pid)
	{
		final_byte = 0;
		bit_index = 0;
	}
	current_client = client_pid;
	final_byte |= bit << bit_index;
	bit_index += 1;
	if (bit_index == 8)
	{
		if (final_byte == 0)
		{
			final_byte = '\n';
			current_client = 0;
		}
		write (STDOUT, &final_byte, 1);
		final_byte = 0;
		bit_index = 0;
	}
}

static void	handle_signal(int sig, siginfo_t *info, void *data)
{
	(void)data;
	if (sig == SIGUSR1)
		receive_bit (info->si_pid, 0);
	else if (sig == SIGUSR2)
		receive_bit (info->si_pid, 1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid ();
	ft_println ("%i", (t_int)pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigaction (SIGUSR1, &sa, NULL);
	sigaction (SIGUSR2, &sa, NULL);
	while (TRUE)
		pause ();
	return (0);
}
