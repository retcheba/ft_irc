/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:38:22 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/02 16:12:45 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <map>
# include <algorithm>
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
    Server( Server const & src );
    ~Server( void );

    Server &    operator=( Server const & rhs );
    void        setPassword( std::string password );
    std::string getPassword( void );
    void        newClient( int sock, std::string username );
    std::string getUsername( int sock );
    void        setBuff( std::string buff );
    void        process( std::string username );

private:

    std::string                 _buff;
    std::string                 _password;
    std::map<int, std::string>  _clients;

};

int create_server( int port );

#endif