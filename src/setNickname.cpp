/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setNickname.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:20:31 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/03 15:54:40 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

static int 	checkFormat(std::string buff)
{
	int i = 5;
	size_t pos;
	std::string user;

	pos = buff.find("NICKNAME ");
	if (pos == std::string::npos || pos != 0)
		return (0);
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != '\0')
		return (0);
	return (1);
}

// void	Server::setNickname(std::string username, std::string buff, int socket)
// {
// 	size_t pos;
// 	std::string clean = cleanString(buff, "NICKNAME ");
	
// 	if (!checkFormat(buff))
// 	{
// 		if (send(socket, "Usage: NICKNAME <message>\n", 34, 0) == -1)
// 			std::cerr << "Error Message can't be sent" << std::endl;
// 		return;
// 	}
// 	if (pos != std::string::npos)
// 	{
// 		clean = cleanString(clean, it->second. + " ");
// 		clean = username + " : " + clean + "\n";
		
// 		if (send(it->first + this->_sock, clean.c_str(), clean.length(), 0) == -1)
// 			std::cerr << "Error Message can't be sent" << std::endl;
// 		break;
// 	}
// 	if (pos == std::string::npos)
// 	{
// 		if (send(socket, "Error : Username not found\n", 27, 0) == -1)
// 			std::cerr << "Error Message can't be sent" << std::endl;
// 	}
		
// }