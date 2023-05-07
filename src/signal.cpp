/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:17:11 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/07 16:22:52 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

extern	Server server;

void	sig_handler(int sig);

// sig=2 -> ^C

void	sig_init(void)
{
	signal(SIGINT, sig_handler);
}

void	sig_handler(int sig)
{
	if (sig == 2)
	{
		server.deleteAllClient();
		server.deleteAllChannel();
		std::cout << std::endl << "Server disconnected" << std::endl;
		exit(0);
	}
}