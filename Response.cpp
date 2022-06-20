#include "Response.hpp"

std::string create_temporary_file(std::string path, std::string file_name, std::string extension)
{
	time_t time_since1970;
  	time_since1970 = time(NULL);
	std::stringstream ss;
	ss << time_since1970;
	std::string time_since1970_string = ss.str();
	std::string tmp_file_path = path + time_since1970_string + "_" + file_name + extension;
	std::ofstream tmp_file(tmp_file_path.c_str());
	tmp_file.close();
	return tmp_file_path;
}

void default_error_page(Response& res, std::string& code, std::string& msg)
{
	std::string error_page_tmp_file = create_temporary_file("/tmp/", "error_page", ".html");
	std::ofstream error_page(error_page_tmp_file.c_str());
	error_page << "<html><head><title>" << code << " " << msg << "</title></head><body><center><h1>" 
	<< code << " " << msg << "</h1></center><hr><center>Webserver</center></body></html>";
	error_page.close();
	res._status_code = code;
	res._body_path = error_page_tmp_file;
	res._headers += "HTTP/1.1 " + res.http_code_map[res._status_code] + "\r\n";
	res._headers += "Server: Webserver/1.0\r\n";
	res._headers += "Date: " + set_date_header() + "\r\n";
	res._headers += "Content-Type: " + res._content_type + "\r\n"; // to be set later
	res._headers += "Content-Length: " + res._content_length + "\r\n";
	res._headers += "\r\n";
}

void init_code_map(Response& res)
{
	res.http_code_map["200"] = "200 OK";
	res.http_code_map["201"] = "201 Created";
	res.http_code_map["202"] = "202 Accepted";
	res.http_code_map["204"] = "204 No Content";
	res.http_code_map["301"] = "301 Move Permanently";
	res.http_code_map["400"] = "400 Bad Request";
	res.http_code_map["403"] = "403 Forbidden";
	res.http_code_map["404"] = "404 Not Found";
	res.http_code_map["405"] = "405 Method Not Allowed";
	res.http_code_map["413"] = "413 Payload Too Large";
	res.http_code_map["414"] = "414 URI Too Long";
	res.http_code_map["500"] = "500 Internal Server Error";
	res.http_code_map["501"] = "501 Not Implemented";
	res.http_code_map["502"] = "502 Bad Gateway";
	res.http_code_map["505"] = "505 HTTP Version Not Supported";
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
	std::string date = std::string(dt);
	return (date.substr(0, date.size() - 1));
}

void set_response_headers(Request& req, Response& res)
{
	res._headers += "HTTP/1.1 " + res.http_code_map[res._status_code] + "\r\n";
	res._headers += "Server: Webserver/1.0\r\n";
	res._headers += "Date: " + set_date_header() + "\r\n";
	res._headers += "Content-Type: " + req.getcontent_type() + "\r\n";
	res._headers += "Content-Length: " + res._content_length + "\r\n";
	// res._headers += "Connection: keep-alive\r\n";
	if (res._special_headers != "")
		res._headers += res._special_headers + "\r\n";
	res._headers += "\r\n";
}

int check_if_entity_exists(std::string path)
{
	struct stat st;
	if (stat(path.c_str(), &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return DIRCODE;
		else if (S_ISREG(st.st_mode))
			return FILECODE;
	}
	return 0;
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
			if (locations[i].get_path() == path)
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
	int nbr_allowed_methods = allowed_methods.size();
	bool found = false;
	for (int i = 0; i < nbr_allowed_methods; i++)
		if (allowed_methods[i] == method)
			found = true;
	if (!found)
	{
		res._status_code = "405";
		std::string allow_header = "Allow: ";
		int nbr_allowed_methods = allowed_methods.size();
		for (int i = 0; i < nbr_allowed_methods; i++)
			allow_header += allowed_methods[i] + ", ";
		res._special_headers += allow_header; 
		throw Response::HttpMethodNotAllowed();
	}
}

void redirect_response(std::pair<std::string, std::string>& redirection, std::string& redirection_code, std::string& redirection_path, Request& req, Response& res)
{
	std::string new_status_code = redirection_code;
	std::string new_location = redirection_path;
	std::string location_header = "Location: " + new_location + "\r\n";
	res._special_headers += location_header;
	res._status_code = new_status_code;
	set_response_headers(req, res);
}

void create_autoindex_file(std::string directory, std::vector<std::string>& entities, Request& req, Response& res)
{
	std::string autoindex_file_path = "/tmp/";
	std::string autoindex_file_name = "autoindex";
	std::string autoindex_file_extension = ".html";
	std::string file_path = create_temporary_file(autoindex_file_path, autoindex_file_name, autoindex_file_extension);
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
	set_response_headers(req, res);
	res._body_path = file_path;
	res._status_code = "200";
	// set content type and length
	file.close();
}

bool check_for_autoindex(std::string directory, Request& req, Response& res)
{
	DIR *dir;
	struct dirent *ent;
	std::vector<std::string> entities;

	if ((dir = opendir(directory.c_str())) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			entities.push_back(ent->d_name);
		}
		closedir(dir);
	}
	else
		throw Response::ForbiddenPath();
	create_autoindex_file(directory, entities, req, res);
}

bool check_for_index_file(Location& location, Response& res)
{
	std::vector<std::string> index_files = location.get_index();
	if (index_files.empty())
	{
		int nbr_indexes = index_files.size();
		for (int i = 0; i < nbr_indexes; i++)
		{
			int index_code = check_if_entity_exists(index_files[i]);
			if (!index_code)
				continue;
			if (index_code == FILECODE && access(index_files[i].c_str(), R_OK) == 0)
			{
				// check if location has cgi
				// set content type and length
				res._body_path = index_files[i];
				res._status_code = "200";
				return true;
			}
			else
				throw Response::ForbiddenPath();		
		}
	}
	return false;
}

void check_directory_resource(std::string& resource, Location& location, Request& req, Response& res)
{
	bool index_file = check_for_index_file(location, res);
	if (!index_file && location.get_auto_index())
		check_for_autoindex(resource, req, res);
	else if (!index_file && !location.get_auto_index())
		throw Response::ForbiddenPath();
}

int requested_resource_by_delete(std::string& resource, Location& location, Response& res)
{
	struct stat st;
	if (stat(resource.c_str(), &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			if (resource.back() != '/')
				throw Response::ConflictError();
			if (access(resource.c_str(), W_OK))
				throw Response::InternalServerError();
			return DIRCODE;
		}
		else if (S_ISREG(st.st_mode))
		{
			if (access(resource.c_str(), W_OK))
				throw Response::ForbiddenPath();
			return FILECODE;
		}
	}
	throw Response::NoMatchedLocation();
}

int requested_resource_by_get(std::string& resource, Location& location, Request& req, Response& res)
{
	struct stat st;
	if (stat(resource.c_str(), &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			if (resource.back() != '/')
			{
				resource += "/";
				std::pair<std::string, std::string> redirections = location.get_redirection();
				res._status_code = "301";
				redirect_response(redirections, res._status_code, resource, req, res);
				return REDIRECTCODE;
			}
			if (access(resource.c_str(), R_OK))
				throw Response::ForbiddenPath();
			return (DIRCODE);
		}
		else if (S_ISREG(st.st_mode))
		{
			if (access(resource.c_str(), R_OK))
				throw Response::ForbiddenPath();
			return (FILECODE);
		}
	}
	else
		throw Response::NoMatchedLocation();
}

int delete_directory(std::string& path)
{
	DIR* dir;
	struct dirent* entry;
	if ((dir = opendir(path.c_str())) != NULL)
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
			{
				if (path.back() != '/')
					path += "/";
				std::string new_path = path + std::string(entry->d_name);
				int entity_type = check_if_entity_exists(new_path);
				if (entity_type == DIRCODE)
				{
					if (delete_directory(new_path))
						return 1;
				}
				else if (entity_type == FILECODE)
				{
					if (remove(new_path.c_str()) != 0)
						return 1;
				}
				else
					return 1;
			}
		}
		if (rmdir(path.c_str()))
			return 1;
		closedir(dir);
		return 0;
	}
	return 1;
}

void response_to_post(Response& res, Request& req, Location& location)
{
	if (!location.get_upload_directory().empty())
	{
		std::string upload_directory = location.get_upload_directory();
		if (upload_directory.back() != '/')
			upload_directory += "/";
		std::string tmp_file_name = "upload_file";
		std::string file_extension = ".txt"; //check mime types later
		std::string file_name = create_temporary_file(upload_directory, tmp_file_name, file_extension);
		std::ofstream file_stream(file_name);
		if (file_stream.is_open())
		{
			//file_stream << req._body; // need request body 
			file_stream.close();
		}
		else
			throw Response::InternalServerError();
		// set response headers and body
	}
	// check if location supports cgi
}

void response_to_delete(Response& res, Request& req, Location& location)
{
	std::string resource = location.get_root() + req.get_requestur();
	int resource_code = requested_resource_by_delete(resource, location, res);

	if (resource_code == DIRCODE)
	{
		if (delete_directory(resource))
			throw Response::InternalServerError();
		res._status_code = "204";
	}
	else if (resource_code == FILECODE)
	{
		if (remove(resource.c_str()) != 0)
			throw Response::InternalServerError();
		res._status_code = "204";
	}
	else
		throw Response::InternalServerError();
}

void response_to_get(Response& res, Request& req, Location& location)
{
	std::string resource = location.get_root() + req.get_requestur();
	int resource_code = requested_resource_by_get(resource, location, req, res);

	if (resource_code == REDIRECTCODE)
		return;
	if (resource_code == DIRCODE)
		check_directory_resource(resource, location, req, res);
	else if (resource_code == FILECODE)
	{
		// check if location has cgi
		// set content type and length
		res._status_code = "200";
		res._body_path = resource;
	}
}

Response custom_and_default_error_pages(Response& res, std::string error_code)
{
	try
	{
		std::map<std::string, std::string> error_map = server.get_errors_map();
		std::string error_page = error_map[error_code];
		std::vector<Location> server_locations = server.get_locations();
		Location errror_location = find_matched_location(error_page, server_locations);
		std::vector<std::string> allowed_methods_in_location = error_location.get_allowed_methods();
		std::string get_error_method = "GET";
		check_allowed_methods(res, get_error_method, allowed_methods_in_location);
		// if (redirection.first != "" && redirection.second != "")
		// {
		// 	redirect_response(redirection, redirection.first,redirection.second, req, res);
		// 	//return res; need to redirect internally in this case or ignore the redirection in error page location
		// }
		return res;
	}
	catch (std::exception& e)
	{
		const char* second_error_code = e.what();
		std::cout << second_error_code << std::endl;
		// get default error page
		default_error_page(res, second_error_code, res.http_code_map[second_error_code]);
		return res;
	}
}

Response server_response(Request& req, Server& server)
{
	Response res;
	init_code_map(res);
	std::vector<std::string> methods_arr = {"GET", "POST", "DELETE"}; 
	void (*methods_ptr[])(Response&, Request&, Location&) = {response_to_get, response_to_post, response_to_delete};

	try
	{
		check_http_version(req.get_httpversion());
		check_supported_methods(req.get_method());
		std::string req_uri = req.get_requestur();
		std::vector<Location> server_locations = server.get_locations();
		Location location = find_matched_location(req_uri, server_locations);
		std::vector<std::string> allowed_methods_in_location = location.get_allowed_methods();
		std::string request_method = req.get_method();
		check_allowed_methods(res, request_method, allowed_methods_in_location);
		std::pair<std::string, std::string> redirection = location.get_redirection();
		if (redirection.first != "" && redirection.second != "")
		{
			redirect_response(redirection, redirection.first,redirection.second, req, res);
			return res;
		}
		for (int i = 0; i < 3; i++)
			if (req.get_method() == methods_arr[i])
				methods_ptr[i](res, req, location);
		return res;
	}
	catch (std::exception& e)
	{
		const char* error_code = e.what();
		// check for error pages
		std::cout << error_code << std::endl;

		return custom_and_default_error_pages(error_code);
	}
}
