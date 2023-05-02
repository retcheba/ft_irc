/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:38:22 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/02 21:24:12 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <map>
# include <algorithm>
# include <cstring>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>

class Server
{

public:

    Server( void );
    ~Server( void );

    void        setPassword( std::string password );
    std::string getPassword( void );
    void        newClient( int sock, std::string username );
	void		deleteClient( int sock );
	void		deleteAllClient( void );
    std::string getUsername( int sock );
    void        setBuff( std::string buff );
    void        process( std::string username, int sockect );

    // SEND
    void	sendMessage(std::string username, std::string buff);

    // CHANNEL
    
    // JOIN

    // NICKNAME

private:

    std::string                 _buff;
    std::string                 _password;
    std::map<int, std::string>  _clients;

};

int		create_server( int port );
void	launch_server( Server &server, int &sock );
bool	check_password( int &sockClient, fd_set &readFds, Server &server );
void	set_username( int &sockClient, int &sock, fd_set &readFds, Server &server, bool &lock );
void	get_input( Server &server, int &fd, int &sock, fd_set &readFds );
void	sig_init(void);

#endif