/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:57:43 by soumanso          #+#    #+#             */
/*   Updated: 2021/12/04 18:57:43 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* Send a byte using SIGUSR1 and SIGUSR2 signals.
 For each BIT in the BYTE, starting from the least significant bit,
 send SIGUSR1 if the bit is 0, and SIGUSR2 if the bit is 1. */
static void	send_byte(pid_t pid, t_u8 byte)
{
	t_int	i;

	i = 0;
	while (i < 8)
	{
		usleep (800);
		if ((byte & 0x01) == 0)
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		byte >>= 1;
		i += 1;
	}
}

int	main(int argc, t_str *args)
{
	pid_t	server_pid;
	t_str	str;

	if (argc != 3)
	{
		ft_println ("Usage: client server_pid string.");
		return (1);
	}
	if (!ft_str_to_int (args[1], &server_pid))
	{
		ft_println ("Expected an integer for argument 0.");
		return (1);
	}
	//str = args[2];
	str = ft_read_entire_file ("minitalk.h", ALLOC_TEMP);
	while (*str)
	{
		send_byte (server_pid, (t_u8)*str);
		str += 1;
	}
	send_byte (server_pid, 0);
	return (0);
}
