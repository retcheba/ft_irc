/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:18:53 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/05 23:03:17 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>

#include "Server.hpp"

class Server;

class Channel
{
	public:

		Channel();
		Channel(int socketUser, std::string User, std::string channelName);
		~Channel();
	
		// MODE SET
		void	setInviteOnly();
		void	setTopicAdminOnly();
		void	setPassWord();
		void	setMaxUser(size_t maxUSer);
		bool	setAdmin(int socketAdmin, int socketNewAdmin, std::string admin);

		// MODE REMOVE
		void	removeInviteOnly();
		void	removeTopicAdminOnly();
		void	removePassWord();
		void	removeMaxUser();
		bool	removeAdmin(int socketAdmin, int socketKick, std::string admin);

		// ADD
		void	addTopic(std::string topic);
		bool	addUser(int socketUser, std::string user, std::string channelName);

		// DELETE
		bool	deleteUser(int socketUser, int socketNewUser, std::string user, std::string channelName);

		// MODE GETTER
		bool	modeInviteOnly() const;
		bool	modeTopicAdminOnly() const;
		bool	modePasswordSet() const;
		bool	modeMaxUserSet() const;

		//GETTER
		bool	getAccesUser(int socketUser, std::string channelName);
		std::string 	getTopic();

		bool	findUser(int socketUser, std::string user, std::string channelName);
		bool	findAdminUser(int socketUser, std::string user, std::string channelName);


	protected:

		bool inviteOnly;
		bool topicAdminOnly;
		bool passwordSet;
		bool maxUserSet;

	private:

		size_t _maxUser;

		std::string _topic;
		std::string _password;

		std::vector<std::string> _accesUser;
		std::vector<std::string> _adminUser;

};

#endif /* ********************************************************* CHANNEL_H */