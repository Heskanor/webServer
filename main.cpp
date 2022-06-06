#include "Client.hpp"

int 	create_socket(const char* host, const char* port)
{
	std::cout << "Configuring local address..." << std::endl;
	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(host, port, &hints, &result) != 0)
	{
		std::cout << "Error: getaddrinfo" << std::endl;
		exit(1);
	}

	std::cout << "Creating socket..." << std::endl;
	int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sockfd < 0)
	{
		std::cout << "Error: socket" << std::endl;
		exit(1);
	}
	
	std::cout << "Binding socket..." << std::endl;
	if (bind(sockfd, result->ai_addr, result->ai_addrlen) == -1)
	{
		std::cout << "Error: bind" << std::endl;
		exit(1);
	}
	freeaddrinfo(result);

	std::cout << "Listening on socket..." << std::endl;
	if (listen(sockfd, 10) < 0)
	{
		std::cout << "Error: listen" << std::endl;
		exit(1);
	}

	return (sockfd);
}

int main()
{
	int server = create_socket("127.0.0.1", "8080");

	while (1)
	{
		fd_set readfds;
		readfds = wait_on_clients(server);
		if (FD_ISSET(server, &readfds))
		{
			Client* client = get_client(-1);
			client->set_sockfd(accept(server, (struct sockaddr*)&(client->get_address_struct()), &(client->get_address_len())));
			if (client->get_sockfd() < 0)
			{
				std::cout << "Error: accept" << std::endl;
				exit(1);
			}
			std::cout << "Client connected: " << client->get_address() << std::endl;
		}
	}
}