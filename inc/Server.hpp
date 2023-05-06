/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:38:22 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/06 14:44:35 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <map>
# include <vector>
# include <algorithm>
# include <cstring>
# include <cerrno>

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# include "User.hpp"
# include "Channel.hpp"

class Channel;

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
    void        clearBuff( void );
    void        setSock( int sock );
    void        process( int socket );
    int			alreadyNickname(std::string buff);

    // SEND
    void            sendMessagePrivate( std::map<int, User>::iterator user, std::string buff );
    void	        sendMessageChannel( std::map<int, User>::iterator user, std::string buff );
    
    // JOIN
    int 	        checkAlreadyChannel(std::string buff);
    void		    createChannel(std::map<int, User>::iterator user, std::string buff);

    // KICK
    void	        kickChannel(std::map<int, User>::iterator user, std::string buff);

    // TOPIC
    void	        topic(std::map<int, User>::iterator user, std::string buff);
    void	        topicChange(std::map<int, User>::iterator user, std::string buff);
    void	        topicView(std::map<int, User>::iterator user, std::string buff);
    
    // UTILIES CMD
    std::map<std::string, Channel>::iterator 	findChannelIterator(std::string channelName);
    bool 	        checkFormatMessage(std::string buff, std::string remove, int i);
    std::string	    cleanStringCmd(std::string buff, std::string remove);
    std::string	    cleanString(std::string buff, std::string remove);
    bool 	        checkLastMessage(std::string buff, std::string cmd);
    
    private:

        int                         _sock;
        std::string                 _buff;
        std::string                 _password;
        std::map<int, User>         _clients;
        std::map<std::string, Channel> _channel;
        // std::vector<std::string>    _channel;

};

//	CREATE SERVER
int		        create_server( int port );
void	        launch_server( int &sock );
void			ignore_message( int &sockClient, fd_set &readFds );
bool	        check_password( int &sockClient, fd_set &readFds );
std::string		set_username( int &sockClient, fd_set &readFds );
void	        set_nickname( int &sockClient, int &sock, fd_set &readFds, std::string user );
void	        get_input( int &fd, int &sock, fd_set &readFds );
//	SIGNAL
void	        sig_init(void);
//	UTILS
void            send_out( int sock, std::string str );
bool			check_end_of_buff( char buff[1024], int num_bytes );
void			clean_buff( char buff[1024] );

#endif