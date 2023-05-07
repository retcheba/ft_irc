/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignoreMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:44:32 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/07 16:44:53 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

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