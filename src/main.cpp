/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:38:22 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/02 16:46:07 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

int	main( int argc, char **argv )
{
	int 				port;
	int 				sock;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	char				buff[1024];
    Server              server;
    bool                lock = false;

    if ( argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	
	port = atoi(argv[1]);
    server.setPassword(argv[2]);

    if ( server.getPassword().empty() )
    {
        std::cerr << "Error: password is empty" << std::endl;
		return 1;
    }

	sock = create_server(port);
	    
	fd_set readFds;

    int loop = sock;
	
    FD_ZERO(&readFds);
    FD_SET(sock, &readFds);

    while (1) 
	{
        
        fd_set tmpFds = readFds;
		
        if (select(loop + 1, &tmpFds, NULL, NULL, NULL) == -1) 
		{
            std::cerr << "select error" << std::endl;
            exit(2);
        }
        for (int fd = 0; fd <= loop; fd++) 
		{
            buff[0] = '\0';
            lock = false;

            if (FD_ISSET(fd, &tmpFds)) 
			{
                if (fd == sock) 
				{
                    int sockClient = accept(sock, (struct sockaddr*)&csin, &cslen);
                    
                    if (sockClient == -1) 
                        std::cerr << "accept error" << std::endl;
					else 
					{
                        FD_SET(sockClient, &readFds);
						
                        if (sockClient > loop)
                            loop = sockClient;
                    
                        while ( ( buff[0] == '\0' || buff[0] == '\n' ) && !lock )
                        {
                            if (send(sockClient, "Password: ", 11, 0) == -1)
                            {
                                std::cerr << "Error during connection" << std::endl;
                                break;
                            }

                            int num_bytes = recv(sockClient, buff, 1023, 0);
    					
                            if (num_bytes == -1)
                            {
                                std::cerr << "Error during connection" << std::endl;
                                break;
                            }
                            else if (num_bytes == 0) 
    					    {
                                std::cerr << "Error during connection" << std::endl;
                                close(sockClient);
                                FD_CLR(sockClient, &readFds);
                                break;
                            }
        					else if ( buff[0] != '\0' && buff[0] != '\n' )
        					{
                                if ( buff[num_bytes - 1] == '\n' )
                                    buff[num_bytes - 1] = '\0';
                                else
                                    buff[num_bytes] = '\0';
        						
                                if ( server.getPassword() == buff )
                                    lock = true;
                                else
                                    buff[0] = '\0';
                                    
                            }
                        }

                        buff[0] = '\0';
                        
                        while ( ( buff[0] == '\0' || buff[0] == '\n' ) && lock )
                        {
                            if (send(sockClient, "Username: ", 11, 0) == -1)
                            {
                                std::cerr << "Error during connection" << std::endl;
                                break;
                            }

                            int num_bytes = recv(sockClient, buff, 1023, 0);
    					
                            if (num_bytes == -1)
                            {
                                std::cerr << "Error during connection" << std::endl;
                                break;
                            }
                            else if (num_bytes == 0) 
    					    {
                                std::cerr << "Error during connection" << std::endl;
                                close(sockClient);
                                FD_CLR(sockClient, &readFds);
                                break;
                            }
        					else if ( buff[0] != '\0' && buff[0] != '\n' )
        					{
                                if ( buff[num_bytes - 1] == '\n' )
                                    buff[num_bytes - 1] = '\0';
                                else
                                    buff[num_bytes] = '\0';
        						
                                std::cout << buff << " connected" << std::endl;
                                
                                server.newClient( ( sockClient - sock ), buff );
                            }
                        }
                    }
                } 
				else 
				{
                    while ( buff[0] == '\0' || buff[0] == '\n' )
                    {
                        int num_bytes = recv(fd, buff, 1023, 0);
    					
                        if (num_bytes == -1)
                        {
                            std::cerr << "Error during message reception" << std::endl;
                            break;
                        }
                        else if (num_bytes == 0) 
    					{
                            std::cout << server.getUsername( fd - sock ) << " disconnected" << std::endl;
                            close(fd);
                            FD_CLR(fd, &readFds);
                            break;
                        } 
    					else if ( buff[0] != '\0' && buff[0] != '\n' )
    					{
                            if ( buff[num_bytes - 1] == '\n' )
                                buff[num_bytes - 1] = '\0';
                            else
                                buff[num_bytes] = '\0';

                            server.setBuff(buff);
                            server.process( server.getUsername( fd - sock ) );
                        }
                    }
                }
            }
        }
    }
    close(sock);
    return 0;
}