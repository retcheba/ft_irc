/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getInput.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:48:34 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/07 16:49:00 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

extern	Server server;

void	get_input( int &fd, int &sock, fd_set &readFds )
{
	char		buff[1024];
	std::string	result;
	bool		OK = false;

	clean_buff(buff);
	while ( OK == false )
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
		if (result.empty())
			OK = false;
	}
	clean_buff(buff);
	return;
}