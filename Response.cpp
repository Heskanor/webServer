#include "Response.hpp"

void init_code_map(void)
{
	code_map[200] = "200 OK";
	code_map[201] = "201 Created";
	code_map[301] = "301 Move Permanently";
	code_map[400] = "400 Bad Request";
	code_map[403] = "403 Forbidden";
	code_map[404] = "404 Not Found";
	code_map[405] = "405 Method Not Allowed";
	code_map[413] = "413 Payload Too Large";
	code_map[414] = "414 URI Too Long";
	code_map[500] = "500 Internal Server Error";
	code_map[501] = "501 Not Implemented";
	code_map[502] = "502 Bad Gateway";
	code_map[505] = "505 HTTP Version Not Supported";
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

void check_allowed_methods(std::string method, std::vector<std::string>& allowed_methods)
{
	if (std::find(allowed_methods.begin(), allowed_methods.end(), method) == allowed_methods.end())
	{
		throw Response::HttpMethodNotAllowed();
	}
}

void check_for_redirect()
{

}

void create_autoindex_file(std:string directory, std::vector<std::string>& entities)
{
	std::ofstream file;
	file.open(directory + "index.html");
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>Index</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<ul>\n";
	for (int i = 0; i < entities.size(); i++)
	{
		file << "<li><a href=\"" << entities[i] << "\">" << entities[i] << "</a></li>\n";
	}
	file << "</ul>\n";
	file << "</body>\n";
	file << "</html>\n";
	file.close();
}

bool check_for_autoindex(std::string directory)
{
	if (location.autoindex)
	{
		if (access(directory, R_OK) == 0)
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
		}
		create_autoindex_file(directory, entities);
		return true;
	}
	return false;
}

void find_requested_resource(std::string& path, Location& location)
{
	std::string resource = location._root + location.path;
	struct stat st;
	if (stat(resource.c_str(), &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			if (!check_for_index_file(location))
			{
				//resource += "/";
				if (!check_for_autoindex(resource))
				{
					throw Response::NoMatchedLocation();
				}
			}
		} 
		else if (S_ISREG(st.st_mode))
		{
			
		} 
	}
	else
	{
		throw Response::NoMatchedLocation();
	}
}

void server_response(Request& req, Server& server)
{

}