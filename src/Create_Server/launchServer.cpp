/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:43:21 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/07 16:43:43 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

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