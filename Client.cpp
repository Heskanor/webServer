#include "Client.hpp"

Client::Client(int sockfd)
{
	this->sockfd = sockfd;
	// innitialize address_len and address
}

int Client::get_sockfd(void)
{
	return (this->sockfd);
}

void Client::set_sockfd(int sockfd)
{
	this->sockfd = sockfd;
}

socklen_t Client::get_address_len(void)
{
	return (this->address_len);
}

struct sockaddr_storage Client::get_address_struct(void)
{
	return (this->address);
}

const char *Client::get_address(void)
{
	// not re-entrant safe
	// static char address_buffer[100];
	char address_buffer[100];
	getnameinfo((struct sockaddr *)&this->address, this->address_len, address_buffer, sizeof(address_buffer), NULL, 0, NI_NUMERICHOST);
	return (address_buffer);
}

Client *get_client(int sockfd)
{
	int nbr_clients = clients.size();

	for (int i = 0; i < nbr_clients; i++)
	{
		if (clients[i].get_sockfd() == sockfd)
			return (&clients[i]);
	}
	Client new_client = Client(sockfd);
	clients.push_back(new_client);
	return (&new_client);
}

void	drop_client(Client* client)
{
	int nbr_clients = clients.size();

	for (int i = 0; i < nbr_clients; i++)
	{
		if (clients[i].get_sockfd() == client->get_sockfd())
		{
			clients.erase(clients.begin() + i);
			close(client->get_sockfd());
			return ;
		}
	}
	std::cerr << "Error: drop_client" << std::endl;
	exit(1);
}

fd_set wait_on_clients(int server_sockfd)
{
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(server_sockfd, &readfds);
	int max_sockfd = server_sockfd;
	int nbr_clients = clients.size();

	for (int i = 0; i < nbr_clients; i++)
	{
		FD_SET(clients[i].get_sockfd(), &readfds);
		if (clients[i].get_sockfd() > max_sockfd)
			max_sockfd = clients[i].get_sockfd();
	}

	if (select(max_sockfd + 1, &readfds, NULL, NULL, NULL) < 0)
	{
		std::cerr << "Error: select" << std::endl;
		exit(1);
	}

	return (readfds);
}

