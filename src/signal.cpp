/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:17:11 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/06 14:48:20 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

extern	Server server;

void	sig_handler(int sig);

/*
sig=3 -> ^\
sig=2 -> ^C
sig=11 -> ^D
*/

void	sig_init(void)
{
	signal(SIGINT, sig_handler);
//	signal(SIGSEGV, sig_handler);
//	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler(int sig)
{
	if (sig == 2)
	{
		server.deleteAllClient();
		std::cout << std::endl << "Server disconnected" << std::endl;
		exit(0);
	}
//	if (sig == 11)
//	{
//		("exit\n");
//		exit(1);
//	}
}