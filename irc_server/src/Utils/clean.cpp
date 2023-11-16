/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:45:44 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:46:05 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

std::string	 Server::cleanString(std::string buff, std::string remove)
{
	size_t pos;
	
	pos = buff.find(remove);
	if (pos != std::string::npos)
		buff.erase(pos, remove.length());
	return (buff);	
}

std::string	 Server::cleanStringCmd(std::string buff, std::string remove)
{
	int i = 0;
	size_t pos;
	std::string clean;
	
	pos = buff.find(remove);
	if (pos != std::string::npos)
		buff.erase(pos, remove.length());
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	clean = buff.substr(0, i);
	return (clean);
}