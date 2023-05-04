/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:38:22 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/04 19:24:53 by luserbu          ###   ########.fr       */
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

# include "User.hpp"

class Server
{

public:

    Server( void );
    ~Server( void );

    void        setPassword( std::string password );
    std::string getPassword( void );
    void        newClient( int sockId, int sock, std::string username, std::string nickname );
	void		deleteClient( int sock );
	void		deleteAllClient( void );
    std::string getUsername( int sock );
    void        setBuff( std::string buff );
    void        setSock( int sock );
    void        process( int socket );

    int 	        alreadyNickname(std::string buff);
    
    // SEND
    void            sendMessagePrivate( std::string username, std::string buff, int socket );
    void	        sendMessageChannel( std::map<int, User>::iterator user, std::string buff );
    
    // JOIN
    int 	        checkAlreadyChannel(std::string buff);
    void		    createChannel(std::map<int, User>::iterator user, std::string buff);

    // KICK
    // void	kickChannel(std::map<int, User>::iterator user, std::string buff);

    // UTILIES CMD
    bool 	        checkFormatMessage(std::string buff, std::string remove, int i);
    std::string	    cleanStringCmd(std::string buff, std::string remove);
    std::string	    cleanString(std::string buff, std::string remove);

    private:

        int                         _sock;
        std::string                 _buff;
        std::string                 _password;
        std::map<int, User>         _clients;
        std::map<int, std::string>  _channel;

};

int		        create_server( int port );
void	        launch_server( Server &server, int &sock );

bool	        check_password( int &sockClient, fd_set &readFds, Server &server );

std::string		set_nickname( int &sockClient, fd_set &readFds, Server &server, bool &lock );
void	        set_username( int &sockClient, int &sock, fd_set &readFds, Server &server, bool &lock, std::string nick );

void	        get_input( Server &server, int &fd, int &sock, fd_set &readFds );
void	        sig_init(void);

#endif