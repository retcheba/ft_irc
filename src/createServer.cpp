/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:00:49 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/06 17:39:32 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

extern	Server server;

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
	std::cout << "Server connected" << std::endl;
	return (sock);
}

void	launch_server( int &sock )
{
	unsigned int		cslen;
	struct sockaddr_in	csin;
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
						
						ignore_message(sockClient, readFds);
						
						if ( check_password(sockClient, readFds) )		
						{
							std::string user = set_username(sockClient, readFds);
							if ( !user.empty() )
								set_nickname(sockClient, sock, readFds, user);
						}
					}
				} 
				else 
					get_input(fd, sock, readFds);
			}
		}
	}
	return;
}

void	ignore_message( int &sockClient, fd_set &readFds )
{
	char	buff[1024];

	clean_buff(buff);
	while ( buff[0] == '\0' )
	{
		int num_bytes = recv(sockClient, buff, 1023, MSG_DONTWAIT);
	
		if (num_bytes == -1)
		{
			if ( errno == EAGAIN || errno == EWOULDBLOCK )
				break;
			std::cerr << "Error during ignoring" << std::endl;
			break;
		}
		else if (num_bytes == 0) 
		{
			std::cerr << "Error during ignoring" << std::endl;
			close(sockClient);
			FD_CLR(sockClient, &readFds);
			break;
		}
		else
			buff[num_bytes] = '\0';
	}
	return;
}

bool	check_password( int &sockClient, fd_set &readFds )
{
	char		buff[1024];
	bool		lock = false;
	std::string	result;
	bool		OK = false;

	clean_buff(buff);
	while ( ( buff[0] == '\0' || buff[0] == '\n' || buff[0] == '\r' ) && !lock )
	{
		if (result.empty())
		{
			if (send(sockClient, "Password: \r\n", 12, 0) == -1)
			{
				std::cerr << "Error during connection" << std::endl;
				break;
			}
		}

		int num_bytes = recv(sockClient, buff, 1024, 0);
	
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
		else if ( buff[0] != '\0' && buff[0] != '\n' && buff[0] != '\r' )
		{
			OK = check_end_of_buff(buff, num_bytes);

			if (result.empty())
				result = static_cast<std::string>(buff);
			else
				result.append(static_cast<std::string>(buff));

			if (OK)
			{
				if ( server.getPassword().compare(result) == 0 )
					lock = true;
				else
				{
					clean_buff(buff);
					result.clear();
				}
			}
			else
				clean_buff(buff);
		}
	}
	return (lock);
}

std::string		set_username( int &sockClient, fd_set &readFds )
{
	char		buff[1024];
	std::string	result;
	bool		OK = false;

	clean_buff(buff);
	while ( buff[0] == '\0' || buff[0] == '\n' || buff[0] == '\r' )
	{
		if (result.empty())
		{
			if (send(sockClient, "Username: \r\n", 12, 0) == -1)
			{
				std::cerr << "Error during connection" << std::endl;
				break;
			}
		}

		int num_bytes = recv(sockClient, buff, 1024, 0);
		
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
		else if ( buff[0] != '\0' && buff[0] != '\n' && buff[0] != '\r' )
		{
			OK = check_end_of_buff(buff, num_bytes);

			if (result.empty())
				result = static_cast<std::string>(buff);
			else
				result.append(static_cast<std::string>(buff));
			
			if (!OK)
				clean_buff(buff);
		}
	}
	return (result);
}

void	set_nickname( int &sockClient, int &sock, fd_set &readFds, std::string user )
{
	char		buff[1024];
	std::string	result;
	bool		OK = false;

	clean_buff(buff);
	while ( buff[0] == '\0' || buff[0] == '\n' || buff[0] == '\r' )
	{
		if (result.empty())
		{
			if (send(sockClient, "Nickname: \r\n", 12, 0) == -1)
			{
				std::cerr << "Error during connection" << std::endl;
				break;
			}
		}

		int num_bytes = recv(sockClient, buff, 1024, 0);
	
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
		else if ( buff[0] != '\0' && buff[0] != '\n' && buff[0] != '\r' )
		{
			OK = check_end_of_buff(buff, num_bytes);

			if (result.empty())
				result = static_cast<std::string>(buff);
			else
				result.append(static_cast<std::string>(buff));
			
			if (!OK)
				clean_buff(buff);
		}
		if (!server.alreadyNickname(buff))
		{
			if (send(sockClient, "Nickname are already use !\r\n", 28, 0) == -1)
			{
				std::cerr << "Error during connection" << std::endl;
				break;
			}
			buff[0] = '\0';
		}
	}
	if ( !result.empty() )
	{
		std::cout << user << "(" << result << ")" << " connected" << std::endl;
		server.newClient( ( sockClient - sock ), sockClient ,user, result );
	}
	
	return;
}

void	get_input( int &fd, int &sock, fd_set &readFds )
{
	char		buff[1024];
	std::string	result;
	bool		OK = false;

	clean_buff(buff);
	while ( buff[0] == '\0' )
	{
		int num_bytes = recv(fd, buff, 1024, 0);
		
		if (num_bytes == -1)
		{
			std::cerr << "Error during message reception" << std::endl;
			break;
		}
		else if (num_bytes == 0)
		{
			std::cout << server.getUsername( fd - sock ) << " disconnected" << std::endl;
			server.deleteClient( fd - sock );
			server.clearBuff();
			if (!buff)
				free(buff);
			close(fd);
			FD_CLR(fd, &readFds);
			break;
		} 
		else
		{
			OK = check_end_of_buff(buff, num_bytes);

			if (result.empty())
				result = static_cast<std::string>(buff);
			else
				result.append(static_cast<std::string>(buff));
			
			if (OK)
			{
				server.setBuff(result);
				server.process( fd - sock );
				server.clearBuff();
			}
			else
				clean_buff(buff);
		}
	}
	clean_buff(buff);
	return;
}
