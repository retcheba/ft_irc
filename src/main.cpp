/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:38:22 by retcheba          #+#    #+#             */
/*   Updated: 2023/04/28 17:01:15 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int	create_server( int port )
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return -1;
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		std::cerr << "Bind error" << std::endl;
		exit(2);
	}
	listen(sock, 42);
	return (sock);
}

int	main( int argc, char **argv )
{
	int 				port;
	int 				sock;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	char				buff[1024];

	if ( argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
		return 1;
	}
	
	port = atoi(argv[1]);
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
            perror("select Error");
            exit(2);
        }
        for (int fd = 0; fd <= loop; fd++) 
		{
            if (FD_ISSET(fd, &tmpFds)) 
			{
                if (fd == sock) 
				{
                    int sockClient = accept(sock, (struct sockaddr*)&csin, &cslen);
                    if (sockClient == -1) 
                        perror("accept");
					else 
					{
                        FD_SET(sockClient, &readFds);
						
                        if (sockClient > loop)
                            loop = sockClient;
                    }
                } 
				else 
				{
                    int num_bytes = recv(fd, buff, 1023, 0);
					
                    if (num_bytes == -1)
                        perror("recv");
                    else if (num_bytes == 0) 
					{
                        std::cout << "Client disconnected" << std::endl;
                        close(fd);
                        FD_CLR(fd, &readFds);
                    } 
					else 
					{
                        buff[num_bytes] = '\0';
                        std::cout << "Received " << num_bytes << " bytes: " << buff << std::endl;
						
                        if (send(fd, "MESSAGE BIEN RECU", 18, 0) == -1)
                            perror("send");
                    }
                }
            }
        }
    }
    close(sock);
    return 0;
}