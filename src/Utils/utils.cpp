/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:48:45 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/07 16:40:35 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	send_out( int sock, std::string str )
{
	size_t	size = str.size();

	if ( send(sock, str.c_str(), size, 0) == -1 )
		std::cerr << "Error Message can't be sent" << std::endl;
	return;
}

bool	check_end_of_buff( char buff[1024], int num_bytes )
{
	bool	OK = false;

	if ( num_bytes >= 2 )
	{
		if ( buff[num_bytes - 2] == '\r' )
		{
			buff[num_bytes - 2] = '\0';
			OK = true;
		}
		else if ( buff[num_bytes - 1] == '\n' )
		{
			buff[num_bytes - 1] = '\0';
			OK = true;
		}
		else
			buff[num_bytes] = '\0';
	}
	else if ( num_bytes >= 1 )
	{
		if ( buff[num_bytes - 1] == '\n' )
		{
			buff[num_bytes - 1] = '\0';
			OK = true;
		}
		else
			buff[num_bytes] = '\0';
	}
	else
		buff[num_bytes] = '\0';

	return (OK);
}

void	clean_buff( char buff[1024] )
{
	for (int i = 0; i < 1024; i++)
		buff[i] = '\0';
	return;
}
