/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setUsername.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:47:00 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/07 16:47:19 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

std::string		set_username( int &sockClient, fd_set &readFds )
{
	char		buff[1024];
	std::string	result;
	bool		OK = false;

	clean_buff(buff);
	while ( OK == false )
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
		if (result.empty())
			OK = false;
	}
	return (result);
}