#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <map>
#include "Response.hpp"
#define MAX_REQUEST_SIZE 1024


class Client {
	public:
		Client(void);
		Client(int);
		Client(std::string, std::string, std::string);
		~Client(void);

		int get_sockfd(void);
		socklen_t get_address_len(void);
		struct sockaddr_storage get_address_struct(void);
		const char *get_address(void);

		void set_sockfd(int);

	private:
		socklen_t address_len;
		struct sockaddr_storage address;
		int sockfd;
		char request[MAX_REQUEST_SIZE + 1];
		int received;
};

Client	*get_client(int sockfd);
void	drop_client(Client* client);
fd_set wait_on_clients(int server_sockfd);

std::vector<Client> clients;

#endif