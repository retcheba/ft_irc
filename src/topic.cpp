/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:33:20 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/05 20:37:44 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

// void	Server::kickChannel(std::map<int, User>::iterator user, std::string buff) {
	
// 	std::string answer;
// 	std::string userName;
// 	std::string channelName;
	
// 	if (!checkFormatMessage(buff, "TOPIC #", 8))
// 	{
// 		answer = "Usage: TOPIC <#channel> <topic>\r\n";
// 		send_out(user->second.getSocket(), answer);
// 		return;
// 	}
// 	channelName = cleanStringCmd(buff, "TOPIC #");
// 	if (checkAlreadyChannel(channelName) == false)
// 	{
// 		answer = "channel has not been created\r\n";
// 		send_out(user->second.getSocket(), answer);
// 		return;
// 	}
// 	if (user->second.findChannel(channelName) == false)
// 	{
// 		answer = "You have not join the channel " + channelName + "\r\n";
// 		send_out(user->second.getSocket(), answer);
// 		return;
// 	}

// }