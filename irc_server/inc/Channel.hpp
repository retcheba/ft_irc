/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:18:53 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/08 19:04:41 by retcheba         ###   ########.fr       */
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

		// CONSTRUCTOR / DESTRUCTOR
		Channel();
		Channel(int socketUser, std::string User, std::string channelName);
		~Channel();
	
		// MODE SET
		void	setInviteOnly(int socketUser, std::string user, std::string channelName);
		void	setTopicAdminOnly(int socketAdminTopic, int socketNewAdminTopic, std::string user, std::string channelName);
		void	setPassWord(int socketUser, std::string user, std::string channelName, std::string password);
		void	setMaxUser(int socketUser, std::string user, std::string channelName, double maxUSer);
		bool	setAdmin(int socketAdmin, int socketNewAdmin, std::string admin);

		// MODE REMOVE
		void	removeInviteOnly(int socketUser, std::string user, std::string channelName);
		void	removePassWord(int socketUser, std::string user, std::string channelName);
		void	removeMaxUser(int socketUser, std::string user, std::string channelName);
		bool	removeAdmin(int socketAdmin, int socketKick, std::string admin);

		// ADD
		void	addTopic(std::string topic);
		void	addPassword(std::string password); 
		bool	addUser(int socketUser, std::string user, std::string channelName);

		// DELETE
		bool	deleteUser(int socketUser, int socketNewUser, std::string user, std::string channelName);
		bool	deleteTopicAdmin(int socketUser, int socketNewUser, std::string user, std::string channelName);
		void	cleanUser(std::string user);

		// MODE BOOLEAN
		bool	modeInviteOnly() const;
		bool	modePasswordSet() const;
		bool	modeMaxUserSet() const;
		
		//GETTER	
		std::string 	getTopic();
		std::string 	getPassword();

		int				channelSize();
		
		double			getMaxUser();

		std::vector<std::string> &	getAcUser( void );
		std::vector<std::string> &	getAdUser( void );
		std::vector<std::string> &	getTopicAdmin( void );
		
		bool	getAccesUser(int socketUser, std::string channelName);

		// FIND
		bool	findUser(std::string user);
		bool	findAdminUser(std::string user);
		bool	findTopicAdmin(std::string user);

		
		
	protected:

		bool inviteOnly;
		bool passwordSet;
		bool maxUserSet;

	private:

		double _maxUser;

		std::string _topic;
		std::string _password;

		std::vector<std::string> _accesUser;
		std::vector<std::string> _adminUser;
		std::vector<std::string> _topicAdmin;

};

#endif /* ********************************************************* CHANNEL_H */