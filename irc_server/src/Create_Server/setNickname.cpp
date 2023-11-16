/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setNickname.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:47:42 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/08 19:23:17 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

extern	Server server;

void	set_nickname( int &sockClient, int &sock, fd_set &readFds, std::string user )
{
	char		buff[1024];
	std::string	result;
	bool		OK = false;

	clean_buff(buff);
	while ( OK == false )
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
		else if (server.checkSpace(buff) == false)
		{
			if (send(sockClient, "Impossible to put SPACE in your username, retry !\r\n", 51, 0) == -1)
			{
				std::cerr << "Error during connection" << std::endl;
				break;
			}
			clean_buff(buff);
		}
		else
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
			clean_buff(buff);
			result.clear();
		}
		if (result.empty())
			OK = false;
	}
	if ( !result.empty() )
	{
		std::cout << user << "(" << result << ")" << " connected" << std::endl;
		server.newClient( ( sockClient - sock ), sockClient ,user, result );
	}
	
	return;
}