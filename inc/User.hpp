/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:19:18 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/04 19:15:33 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>
# include <map>

class User
{
	public:

		User();
		User(std::string user, std::string nick, int sock);
		~User();

		
		// GETTER
		std::string getUser(void);
		std::string getNick(void);
		int			getSocket(void);

		// SETTER
		void		setUser(std::string user);
		void		setNick(std::string nick);
		void		setChan(std::string chan, bool admin);
		void		setSocket(int sock);

		bool 		findChannel(std::string chan);
		bool		checkAdminChannel(std::string chan);

		void		deleteChannel(std::string chan);

	private:

		std::string _username;
		std::string _nickname;
		std::map<int, std::string> _channel;
		int         _socket;

};

#endif /* ************************************************************ USER_H */