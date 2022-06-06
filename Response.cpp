#include "Response.hpp"

void send_400(Client* client)
{
	std::string response = "HTTP/1.1 400 Bad Request\r\n"
		"Connection: close\r\n"
		"Content-Length: 11\r\n\r\nBad Request";
	send(client->get_sockfd(), response.c_str(), response.size(), 0);
	drop_client(client);
}

void send_404(Client* client)
{
	std::string response = "HTTP/1.1 404 Not Found\r\n\r\n"
		"Connection: close\r\n"
		"Content-Length: 9\r\n\r\nNot Found";
	send(client->get_sockfd(), response.c_str(), response.size(), 0);
	drop_client(client);
}

void serve_resource(Client* client, std::string resource)
{
	// For debugging purposes
	std::cout << "Serve resource: " << client->get_client_address() << " " << resource << std::endl;
	
	std::string response = "HTTP/1.1 200 OK\r\n"
		"Connection: close\r\n"
		"Content-Length: " + std::to_string(resource.size()) + "\r\n\r\n" + resource;
	send(client->get_sockfd(), response.c_str(), response.size(), 0);
	drop_client(client);
}	
