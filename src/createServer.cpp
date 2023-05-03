/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:00:49 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/03 17:58:12 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

int create_server( int port )
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return -1;
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		std::cerr << "Bind error" << std::endl;
		exit(2);
	}
	listen(sock, 42);
	return (sock);
}

void	launch_server( Server &server, int &sock )
{
	unsigned int		cslen;
	struct sockaddr_in	csin;
	bool				lock = false;
	fd_set				readFds;
	int					loop = sock;
	
	FD_ZERO(&readFds);
	FD_SET(sock, &readFds);

	sig_init();

	while (1) 
	{
		fd_set tmpFds = readFds;
		
		if (select(loop + 1, &tmpFds, NULL, NULL, NULL) == -1) 
		{
			std::cerr << "select error" << std::endl;
			exit(2);
		}
		for (int fd = 0; fd <= loop; fd++) 
		{
			if (FD_ISSET(fd, &tmpFds)) 
			{
				if (fd == sock)
				{
					cslen = sizeof(csin);
					int sockClient = accept(sock, (struct sockaddr*)&csin, &cslen);
					
					if (sockClient == -1) 
						std::cerr << "accept error" << std::endl;
					else 
					{
						FD_SET(sockClient, &readFds);
						
						if (sockClient > loop)
							loop = sockClient;
						
						lock = false;
						
						lock = check_password(sockClient, readFds, server);		

						set_username(sockClient, sock, readFds, server, lock);
					}
				} 
				else 
					get_input(server, fd, sock, readFds);
			}
		}
	}
	return;
}

bool	check_password( int &sockClient, fd_set &readFds, Server &server )
{
	char	buff[1024];
	bool	lock = false;

	buff[0] = '\0';
	while ( ( buff[0] == '\0' || buff[0] == '\n' ) && !lock )
	{
		if (send(sockClient, "Password: ", 11, 0) == -1)
		{
			std::cerr << "Error during connection" << std::endl;
			break;
		}

		int num_bytes = recv(sockClient, buff, 1023, 0);
	
		if (num_bytes == -1)
		{
			std::cerr << "Error during connection" << std::endl;
			break;
		}
		else if (num_bytes == 0) 
		{
			std::cerr << "Error during connection" << std::endl;
			close(sockClient);
			FD_CLR(sockClient, &readFds);
			break;
		}
		else if ( buff[0] != '\0' && buff[0] != '\n' )
		{
			if ( buff[num_bytes - 1] == '\n' )
				buff[num_bytes - 1] = '\0';
			else
				buff[num_bytes] = '\0';
			
			if ( server.getPassword() == buff )
				lock = true;
			else
				buff[0] = '\0';
		}
	}
	return (lock);
}

void	set_username( int &sockClient, int &sock, fd_set &readFds, Server &server, bool &lock )
{
	char	buff[1024];

	buff[0] = '\0';
	while ( ( buff[0] == '\0' || buff[0] == '\n' ) && lock )
	{
		if (send(sockClient, "Username: ", 11, 0) == -1)
		{
			std::cerr << "Error during connection" << std::endl;
			break;
		}

		int num_bytes = recv(sockClient, buff, 1023, 0);
	
		if (num_bytes == -1)
		{
			std::cerr << "Error during connection" << std::endl;
			break;
		}
		else if (num_bytes == 0) 
		{
			std::cerr << "Error during connection" << std::endl;
			close(sockClient);
			FD_CLR(sockClient, &readFds);
			break;
		}
		else if ( buff[0] != '\0' && buff[0] != '\n' )
		{
			if ( buff[num_bytes - 1] == '\n' )
				buff[num_bytes - 1] = '\0';
			else
				buff[num_bytes] = '\0';
			
			std::cout << buff << " connected" << std::endl;
			
			server.newClient( ( sockClient - sock ), sockClient ,buff );
		}
	}
	return;
}

void	get_input( Server &server, int &fd, int &sock, fd_set &readFds )
{
	char	buff[1024];

	buff[0] = '\0';
	while ( buff[0] == '\0' || buff[0] == '\n' )
	{
		int num_bytes = recv(fd, buff, 1023, 0);
		
		if (num_bytes == -1)
		{
			std::cerr << "Error during message reception" << std::endl;
			break;
		}
		else if (num_bytes == 0) 
		{
			std::cout << server.getUsername( fd - sock ) << " disconnected" << std::endl;
			server.deleteClient( fd - sock );
			close(fd);
			FD_CLR(fd, &readFds);
			break;
		} 
		else if ( buff[0] != '\0' && buff[0] != '\n' )
		{
			if ( buff[num_bytes - 1] == '\n' )
				buff[num_bytes - 1] = '\0';
			else
				buff[num_bytes] = '\0';

			server.setBuff(buff);
			server.process( fd - sock );
		}
	}
	return;
}
