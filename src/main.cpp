/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:58:41 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/08 13:02:32 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server	server;

int	main( int argc, char **argv )
{
	int 				port;
	int 				sock;

	if ( argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	
	port = atoi(argv[1]);
	
	if (server.checkSpace(argv[2]) == false)
	{
		std::cerr << "Impossible to put SPACE in password, retry !\n" << std::endl;
		return (2);
	}

	server.setPassword(argv[2]);

	if ( server.getPassword().empty() )
	{
		std::cerr << "Error: password is empty" << std::endl;
		return 1;
	}

	sock = create_server(port);
	server.setSock(sock);
	launch_server(sock);

	close(sock);
	return 0;
}