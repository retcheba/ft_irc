/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:58:41 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/02 18:49:18 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

int	main( int argc, char **argv )
{
	int 				port;
	int 				sock;
	Server				server;

	if ( argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	
	port = atoi(argv[1]);
	server.setPassword(argv[2]);

	if ( server.getPassword().empty() )
	{
		std::cerr << "Error: password is empty" << std::endl;
		return 1;
	}

	sock = create_server(port);

	launch_server(server, sock);

	close(sock);
//	server.deleteAllClient();
	return 0;
}