#include "Response.hpp"

std::string deffault_error_page(std::string& code, std::string& msg)
{
	std::string page;
	page = "<html><head><title>" + code + " " + msg + "</title></head><body><center><h1>" 
	+ code + " " + msg + "</h1></center><hr><center>Webserver</center></body></html>";
	return page;
}

void init_code_map(void)
{
	code_map["200"] = "200 OK";
	code_map["201"] = "201 Created";
	code_map["301"] = "301 Move Permanently";
	code_map["400"] = "400 Bad Request";
	code_map["403"] = "403 Forbidden";
	code_map["404"] = "404 Not Found";
	code_map["405"] = "405 Method Not Allowed";
	code_map["413"] = "413 Payload Too Large";
	code_map["414"] = "414 URI Too Long";
	code_map["500"] = "500 Internal Server Error";
	code_map["501"] = "501 Not Implemented";
	code_map["502"] = "502 Bad Gateway";
	code_map["505"] = "505 HTTP Version Not Supported";
}

// HTTP/1.1 403 Forbidden
// Server: nginx/1.21.6
// Date: Sun, 12 Jun 2022 02:41:52 GMT
// Content-Type: text/html
// Content-Length: 555
// Connection: keep-alive

std::string set_date_header()
{
	time_t ttime = time(0);
    char* dt = ctime(&ttime);
	string date = string(dt);
	return (date.substr(0, date.size() - 1));
}

void set_response_headers(Request& req, Response& res)
{
	res._headers += "HTTP/1.1 " + res._status_code + " " + code_map[res._status_code] + "\r\n";
	res._headers += "Server: Webserver/1.0\r\n";
	res._headers += "Date: " + set_date_header() + "\r\n";
	res._headers += "Content-Type: " + req.content_type + "\r\n";
	res._headers += "Content-Length: " + res._content_length + "\r\n";
	// res._headers += "Connection: keep-alive\r\n";
	if (res._special_headers != "")
		res._headers += res._special_headers + "\r\n";
	res._headers += "\r\n";
}

bool check_if_entity_exists(std::string path)
{
	struct stat st;
	if (stat(path.c_str(), &st) == 0)
	{
		return true;
	}
	return false;
}

void check_http_version(std::string version)
{
	if (version != "HTTP/1.1")
	{
		throw Response::InvalidHttpVersion();
	}
}

void check_supported_methods(std::string method)
{
	if (method != "GET" && method != "POST" && method != "DELETE")
	{
		throw Response::HttpMethodNotSupported();
	}
}


Location find_matched_location(std::string& path, std::vector<Location>& locations)
{
	if (path != "")
	{
		int nbr_locations = locations.size();
		for (int i = 0; i < nbr_locations; i++)
		{
			if (locations[i].path == path)
				return locations[i];
		}
		size_t found = path.find_last_of("/");
		if (found != std::string::npos)
		{
			std::string path_without_last_slash = path.substr(0, found);
			return find_matched_location(path_without_last_slash, locations);
		}
	}
	throw Response::NoMatchedLocation();
}

void check_allowed_methods(Response& res, std::string method, std::vector<std::string>& allowed_methods)
{
	if (std::find(allowed_methods.begin(), allowed_methods.end(), method) == allowed_methods.end())
	{
		res._status_code = "405";
		res._special_headers = "Allow: " + string_join(allowed_methods, ", ");
		throw Response::HttpMethodNotAllowed();
	}
}

void check_for_redirect(std::vector<std::pair<std::string, std::string>>& redirections, Response& res)
{
	if (redirections.size() == 0)
		return;
	std::string new_status_code = redirections[0].first;
	std::string new_location = redirections[0].second;
	std::string location_header = "Location: " + new_location + "\r\n";
	res._status_code = new_status_code;
	set_response_headers(req, res, location_header);
}

void create_autoindex_file(std:string directory, std::vector<std::string>& entities, Response& res)
{
	std::string file_path = "/tmp/autoindex.html";
	std::ofstream file;
	file.open(file_path);
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>Index of " << directory << "</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<h1>Index of "<< directory <<"</h1>\n";
	file << "<hr>\n";
	file << "<pre>\n";
	file << "<a href=" << "../" << ">../</a>\n";
	for (int i = 0; i < entities.size(); i++)
	{
		file << "<a href=\"" << entities[i] << "\">" << entities[i] << "</a>\n";
	}
	file << "</pre>\n";
	file << "<hr>\n";
	file << "</body>\n";
	file << "</html>\n";
	set_response_headers(req, res, "");
	res._body_path = file_path;
	file.close();
}

bool check_for_autoindex(std::string directory, Response& res)
{
	DIR *dir;
	struct dirent *ent;
	std::vector<std::string> entities;

	if ((dir = opendir(directory)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			entities.push_back(ent->d_name);
		}
	}
	closedir(dir);
	create_autoindex_file(directory, entities, res);
}

void check_for_index_file(Location& location, Response& res)
{
	if (!location._index.empty())
	{
		int nbr_indexes = location._index.size();
		for (int i = 0; i < nbr_indexes; i++)
		{
			if (!check_if_entity_exists(location._index[i]))
				continue;	
			if (access(location._index[i].c_str(), R_OK) == 0)
			{
				// check if it is a directory
				res._body_path = location._index[i];
				return true;
			}
			else
				throw Response::ForbiddenPath();		
		}
	}
	return false;
}

void check_directory_resource(std::string& resource, Location& location, Response& res)
{
	bool index_file = check_for_index_file(location, res);
	if (!index_file && location.autoindex)
		check_for_autoindex(resource, res);
	else if (!index_file && !location.autoindex)
		throw Response::ForbiddenPath();
}

int find_requested_resource(std::string& resource, Location& location, Response& res)
{
	struct stat st;
	if (stat(resource.c_str(), &st) == 0)
	{
		// will modify access permissions later depending on the method
		// if resource is directory with out / at the end redirect to directory/ before checking permission 
		// if (S_ISDIR(st.st_mode))
		// {
		// 	if (resource.back() != '/')
		// 	{
		// 		resource += "/";
		// 		return find_requested_resource(resource, location, res);
		// 	}
		// 	check_directory_resource(resource, location, res);
		// }
		if (access(resource.c_str(), R_OK))
			throw Response::ForbiddenPath();
		if (S_ISDIR(st.st_mode))
			return (DIRCODE);
		else if (S_ISREG(st.st_mode))
			return (FILECODE);
	}
	else
		throw Response::NoMatchedLocation();
}

void get_method(Response& res, Request& req, Location& location)
{
	std::string resource = location._root + location._path;
	int resource_code = find_requested_resource(resource, location, res);

	if (resource_code == DIRCODE)
		check_directory_resource(resource, location, res);
	else if (resource_code == FILECODE)
	{
		// check if it's extension is a MimeType / cgi
		res._body_path = resource;
	}
}

Response server_response(Request& req, Server& server)
{
	Response res;
	init_code_map();
	vector<std::string> methods_arr = {"GET", "POST", "DELETE"}; 
	void (*methods_ptr[])(Response&, Request&, Location&) = {get_method, post_method, delete_method};

	try
	{
		check_http_version(req.get_httpversion(););
		check_supported_methods(req.get_method());
		Location location = find_matched_location(req.get_requestur(), server.locations);
		check_allowed_methods(req.get_method(), location.allowed_methods);
		//redirection
		for (int i = 0; i < 3; i++)
			if (req.get_method() == methods_arr[i])
				methods_ptr[i](res, req, location);
		// std::string resource = location._root + location._path;
		// int resource_code = find_requested_resource(resource, location, res);
		// if (resource_code == DIRCODE)
		// 	check_directory_resource(resource, location, res);
		// else if (resource_code == FILECODE)
		// {
		// 	// check if it's extension is a MimeType
		// 	res._body_path = resource;
		// }
	}
	catch (std::exception& e)
	{
		char* error_code = e.what();
		// check for error pages
	}
}

