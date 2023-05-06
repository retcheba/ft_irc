/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:18:53 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/06 17:13:13 by luserbu          ###   ########.fr       */
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
		void	setInviteOnly(int socketUser, std::string user, std::string channelName);
		void	setTopicAdminOnly(int socketUser, std::string user, std::string channelName);
		void	setPassWord(int socketUser, std::string user, std::string channelName, std::string password);
		void	setMaxUser(int socketUser, std::string user, std::string channelName, double maxUSer); //push
		bool	setAdmin(int socketAdmin, int socketNewAdmin, std::string admin);

		// MODE REMOVE
		void	removeInviteOnly(int socketUser, std::string user, std::string channelName);
		void	removeTopicAdminOnly(int socketUser, std::string user, std::string channelName);
		void	removePassWord(int socketUser, std::string user, std::string channelName);
		void	removeMaxUser(int socketUser, std::string user, std::string channelName);
		bool	removeAdmin(int socketAdmin, int socketKick, std::string admin);

		// ADD
		void	addTopic(std::string topic);
		void	addPassword(std::string password); 
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
		std::string 	getPassword();
		double			getMaxUser();
		std::vector<std::string> &	getAcUser( void );
		std::vector<std::string> &	getAdUser( void );

		bool	findUser(std::string user);
		bool	findAdminUser(std::string user);
		int		channelSize();


	protected:

		bool inviteOnly;
		bool topicAdminOnly;
		bool passwordSet;
		bool maxUserSet;

	private:

		double _maxUser; // push

		std::string _topic;
		std::string _password;

		std::vector<std::string> _accesUser;
		std::vector<std::string> _adminUser;

};

#endif /* ********************************************************* CHANNEL_H */