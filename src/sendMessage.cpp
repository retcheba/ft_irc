/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:17:31 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/02 22:28:55 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"
	
std::string	 cleanString(std::string buff, std::string remove)
{
	size_t pos;
	
	pos = buff.find(remove);
	if (pos != std::string::npos)
		buff.erase(pos, remove.length());
	return (buff);	
}

static int 	checkFormat(std::string buff)
{
	int i = 5;
	size_t pos;
	std::string user;

	pos = buff.find("SEND ");
	if (pos == std::string::npos || pos != 0)
		return (0);
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != ' ')
		return (0);
	if (buff[i + 1] == '\0')
		return (0);
	return (1);
}

void	Server::sendMessage(std::string username, std::string buff, int socket)
{
	size_t pos;
	std::map<int, std::string>::iterator    it = _clients.begin();
	std::string clean = cleanString(buff, "SEND ");
	
	if (!checkFormat(buff))
	{
		if (send(socket, "Usage: SEND <username> <message>\n", 34, 0) == -1)
			std::cerr << "Error Message can't be sent" << std::endl;
		return;
	}
	for ( std::map<int, std::string>::iterator ite = _clients.end(); it != ite; it++ )
	{
		pos = clean.find(it->second);
		if (pos != std::string::npos)
		{
			clean = cleanString(clean, it->second + " ");
			clean = username + " : " + clean + "\n";
			
			if (send(it->first + this->_sock, clean.c_str(), clean.length(), 0) == -1)
				std::cerr << "Error Message can't be sent" << std::endl;
			break;
		}
	}
	if (pos == std::string::npos)
	{
		if (send(socket, "Error : Username not found\n", 27, 0) == -1)
			std::cerr << "Error Message can't be sent" << std::endl;
	}
		
}

