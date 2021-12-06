/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:57:43 by soumanso          #+#    #+#             */
/*   Updated: 2021/12/06 17:29:32 by soumanso         ###   ########lyon.fr   */
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
		usleep (100);
		if ((byte & 0x01) == 0)
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		byte >>= 1;
		i += 1;
	}
}

static void	send_string(pid_t pid, t_str str)
{
	while (*str)
	{
		send_byte (pid, (t_u8)(*str));
		str += 1;
	}
	send_byte (pid, 0);
}

static t_bool	parse_int(t_str str, t_int *out)
{
	t_u64	un;
	t_int	sign;
	t_s64	i;

	i = 0;
	un = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		i += 1;
		sign = (*str == '+') * 2 - 1;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		un *= 10;
		un += str[i] - '0';
		i += 1;
	}
	if (out)
		*out = un * sign;
	return (TRUE);
}

int	main(int argc, t_str *args)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_fprintln (STDERR, "Usage: client server_pid string");
		return (1);
	}
	if (!parse_int (args[1], &server_pid))
	{
		ft_fprintln (STDERR, "Expected an integer for argument 0.");
		return (1);
	}
	if (server_pid < 0)
	{
		ft_fprintln (STDERR, "Invalid PID (%i).", (t_int)server_pid);
		return (1);
	}
	send_string (server_pid, ft_read_entire_file ("testfile", ALLOC_TEMP));
	return (0);
}
