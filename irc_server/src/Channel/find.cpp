/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:16:52 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:17:47 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/*
** --------------------------------- FIND ----------------------------------
*/

bool	Channel::findUser(std::string user) {

	std::string answer;
	std::vector<std::string>::iterator itAcces = _accesUser.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == user)
			return (true);
		itAcces++;
	}
	return (false);
}

bool	Channel::findAdminUser(std::string user) {

	std::string answer;
	std::vector<std::string>::iterator itAdmin = _adminUser.begin();

	while (itAdmin != _adminUser.end())
	{
		if (*itAdmin == user)
			return (true);
		itAdmin++;
	}
	return (false);
}

bool	Channel::findTopicAdmin(std::string user) {

	std::string answer;
	std::vector<std::string>::iterator itTopic = _topicAdmin.begin();

	while (itTopic != _topicAdmin.end())
	{
		if (*itTopic == user)
			return (true);
		itTopic++;
	}
	return (false);
}

/* ************************************************************************** */