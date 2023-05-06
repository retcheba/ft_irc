/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:16:15 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/06 16:04:30 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel()
{
}

Channel::Channel(int socketUser, std::string User, std::string channelName)
{
	std::string answer;
	
	_adminUser.push_back(User);
	_accesUser.push_back(User);

	this->_maxUser = 0;

	this->maxUserSet = false;
	this->inviteOnly = false;
	this->topicAdminOnly = false;
	this->passwordSet = false;

	answer = "Channel: #" + channelName + " has been created\r\n";
	send_out(socketUser, answer);
	
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}


/*
** --------------------------------- MODE SET ----------------------------------
*/

void	Channel::setInviteOnly(int socketUser, std::string user, std::string channelName) {

	std::string answer;

	if (inviteOnly == true)
	{
		answer = "Mode invite only already set !\r\n";
		send_out(socketUser, answer);
		return ;
	}		
	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	
	answer = "Mode invite only are set !\r\n";
	send_out(socketUser, answer);
	inviteOnly = true;
}

void	Channel::setTopicAdminOnly(int socketUser, std::string user, std::string channelName) {

	std::string answer;
	if (topicAdminOnly == true)
	{
		answer = "Mode topic admin are already set !\r\n";
		send_out(socketUser, answer);
		return ;
	}		
	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	
	answer = "Mode topic admin are set !\r\n";
	send_out(socketUser, answer);
	topicAdminOnly = true;
}

void	Channel::setPassWord(int socketUser, std::string user, std::string channelName, std::string password) {

	std::string answer;

	if (passwordSet == true)
	{
		answer = "Password are already set !\r\n";
		send_out(socketUser, answer);
		return ;
	}	
	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	
	answer = "Password are set !\r\n";
	send_out(socketUser, answer);
	addPassword(password);
	passwordSet = true;
}

void	Channel::setMaxUser(size_t maxUSer) {
	
	maxUserSet = true;
	this->_maxUser = maxUSer;
}

bool	Channel::setAdmin(int socketAdmin, int socketNewAdmin, std::string admin) {
	
	std::string answer;
	std::vector<std::string>::iterator itAcces = _accesUser.begin();
	std::vector<std::string>::iterator itAdmin = _adminUser.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == admin)
		{
			while (itAdmin != _adminUser.end())
			{
				if (*itAdmin == admin)
				{
					answer = admin + " are already an admin\r\n";
					send_out(socketAdmin, answer);
					return (false);
				}
				itAdmin++;
			}
			_adminUser.push_back(admin);
			answer = admin + " are an admin\r\n";
			send_out(socketAdmin, answer);
			answer = "you are an admin\r\n";
			send_out(socketNewAdmin, answer);
			return (true);
		}
		itAcces++;
	}
	answer = admin + " does not exist in channel\r\n";
	send_out(socketAdmin, answer);
	return (false);
}

/*
** --------------------------------- MODE REMOVE ----------------------------------
*/

void	Channel::removeInviteOnly(int socketUser, std::string user, std::string channelName) {

	std::string answer;
	
	if (topicAdminOnly == false)
	{
		answer = "Mode invite only are already remove !\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	
	answer = "Mode invite only are remove !\r\n";
	send_out(socketUser, answer);
	inviteOnly = false;
}

void	Channel::removeTopicAdminOnly(int socketUser, std::string user, std::string channelName) {

	std::string answer;
	
	if (topicAdminOnly == false)
	{
		answer = "Mode topic admin are already remove !\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	
	answer = "Mode topic admin are remove !\r\n";
	send_out(socketUser, answer);
	topicAdminOnly = false;
}

void	Channel::removePassWord(int socketUser, std::string user, std::string channelName) {

	std::string answer;
	
	if (passwordSet == false)
	{
		answer = "Password are already remove !\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	
	answer = "Password are remove !\r\n";
	send_out(socketUser, answer);
	addPassword("");
	passwordSet = false;
}

void	Channel::removeMaxUser() {

	maxUserSet = false;
}

bool	Channel::removeAdmin(int socketAdmin, int socketKick, std::string admin) {

	std::string answer;
	std::vector<std::string>::iterator itAdmin = _adminUser.begin();

	while (itAdmin != _adminUser.end())
	{
		if (*itAdmin == admin)
		{
			_adminUser.erase(itAdmin);
			answer = admin + " is no longer an admin\r\n";
			send_out(socketAdmin, answer);
			answer = "you are no longer an admin\r\n";
			send_out(socketKick, answer);
			return (true);
		}
		itAdmin++;
	}
	answer = admin + " does not exist in channel\r\n";
	send_out(socketAdmin, answer);
	return (false);
}

/*
** --------------------------------- ADD ----------------------------------
*/

void	Channel::addTopic(std::string topic) {

	this->_topic = topic;
}

void	Channel::addPassword(std::string password) {

	this->_password = password;
}

bool	Channel::addUser(int socketUser, std::string user, std::string channelName) {

	std::string answer;
	std::vector<std::string>::iterator itAcces = _accesUser.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == user)
		{
			answer = user + " are already exist in channel\r\n";
			send_out(socketUser, answer);
			return (false);
		}
		itAcces++;
	}
	_accesUser.push_back(user);
	answer = "You have join channel #" + channelName + "\r\n";
	send_out(socketUser, answer);
	// answer = "you are added in channel #" + channelName + "\r\n";
	// send_out(socketNewUser, answer);
	return (true);
}

/*
** --------------------------------- DELETE ----------------------------------
*/

bool	Channel::deleteUser(int socketUser, int socketNewUser, std::string user, std::string channelName) {

	std::string answer;
	std::vector<std::string>::iterator itAcces = _accesUser.begin();
	std::vector<std::string>::iterator itAdmin = _adminUser.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == user)
		{
			while (itAdmin != _adminUser.end())
			{
				if (*itAdmin == user)
				{
					_adminUser.erase(itAdmin);
					break;
				}
				itAdmin++;
			}
			_accesUser.erase(itAcces);
			answer = user + " has been removed from the channel\r\n";
			send_out(socketUser, answer);
			answer = "you has been removed from the channel #" + channelName + "\r\n";
			send_out(socketNewUser, answer);
			return (true);
		}
		itAcces++;
	}
	answer = user + " does not exist in channel\r\n";
	send_out(socketNewUser, answer);
	return (false);
}

/*
** --------------------------------- MODE GETTER ----------------------------------
*/

bool	Channel::modeInviteOnly() const {

	return(this->inviteOnly);
}

bool	Channel::modeTopicAdminOnly() const {
	
	return(this->topicAdminOnly);
}

bool	Channel::modePasswordSet() const {

	return(this->passwordSet);
}

bool	Channel::modeMaxUserSet() const {

	return(this->maxUserSet);
}

/*
** --------------------------------- GETTER ----------------------------------
*/

bool		Channel::getAccesUser(int socketUser, std::string channelName) {
	
	std::string answer;
	std::vector<std::string>::iterator itAcces = _accesUser.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == channelName)
		{
			answer = "You are already in channel #" + channelName + "\r\n";
			send_out(socketUser, answer);
			return (true);
		}
		itAcces++;
	}
	return (false);
}

std::string 	Channel::getTopic() {
	
	return (this->_topic);
}


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

std::vector<std::string> &	Channel::getAcUser( void )
{
	return (this->_accesUser);
}

std::vector<std::string> &	Channel::getAdUser( void )
{
	return (this->_adminUser);
}

/* ************************************************************************** */