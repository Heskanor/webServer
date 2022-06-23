#include "Response.hpp"

std::string create_tmp_file_name(std::string path, std::string file_name, std::string extension)
{
	time_t time_since1970;
  	time_since1970 = time(NULL);
	std::stringstream ss;
	ss << time_since1970;
	std::string time_since1970_string = ss.str();
	return (path + time_since1970_string + "_" + file_name + extension);
}

std::string create_temporary_file(std::string path, std::string file_name, std::string extension)
{
	std::string tmp_file_path = create_tmp_file_name(path, file_name, extension);
	std::ofstream tmp_file(tmp_file_path.c_str());
	tmp_file.close();
	return tmp_file_path;
}

std::string better_to_string(int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string set_date_header()
{
	time_t ttime = time(0);
    char* dt = ctime(&ttime);
	std::string date = std::string(dt);
	return (date.substr(0, date.size() - 1));
}

int get_file_size(std::string& file_path)
{
	struct stat st;
	stat(file_path.c_str(), &st);
	return st.st_size;
}

void set_content_type_and_length(Request& req, Response& res, std::string& file_path)
{
	MimeType mime_type;
	std::string extension = file_path.substr(file_path.find_last_of("."));
	res._content_type = mime_type.get_mime_type(extension);
	res._content_length = get_file_size(file_path);
}

void default_error_page(Response& res)
{
	std::string error_page_tmp_file = create_temporary_file("/tmp/", "error_page", ".html");
	std::ofstream error_page(error_page_tmp_file.c_str());
	error_page << "<html><head><title>" << res.http_code_map[res._status_code] << "</title></head><body><center><h1>" 
	<< res.http_code_map[res._status_code] << "</h1></center><hr><center>Webserver</center></body></html>";
	error_page.close();
	res._tmp_file_path = error_page_tmp_file;
	res._headers += "HTTP/1.1 " + res.http_code_map[res._status_code] + "\r\n";
	res._headers += "Server: Webserver/1.0\r\n";
	res._headers += "Date: " + set_date_header() + "\r\n";
	res._headers += "Content-Type: text/html\r\n";
	res._content_length = get_file_size(error_page_tmp_file);
	res._headers += "Content-Length: " + better_to_string(res._content_length) + "\r\n";
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

void set_response_headers(Request& req, Response& res)
{
	res._headers += "HTTP/1.1 " + res.http_code_map[res._status_code] + "\r\n";
	res._headers += "Server: Webserver/1.0\r\n";
	res._headers += "Date: " + set_date_header() + "\r\n";
	if (res._content_type != "")
	{
		res._headers += "Content-Type: " + res._content_type + "\r\n";
		res._headers += "Content-Length: " + better_to_string(res._content_length) + "\r\n";
	}
	if (res._special_headers != "")
		res._headers += res._special_headers + "\r\n";
	res._headers += "\r\n";
}

int check_if_entity_exists(std::string path)
{
	std::cout << "Checking if entity exists: " << path << std::endl;
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

void redirect_response(std::string& redirection_code, std::string& redirection_path, Request& req, Response& res)
{
	std::string new_status_code = redirection_code;
	std::string new_location = redirection_path;
	std::string location_header = "Location: " + new_location + "\r\n";
		// std::string location_header = "Location: " + new_location + "\r\n";

	res._special_headers += location_header;
	res._status_code = new_status_code;
	set_response_headers(req, res);
}

bool check_if_cgi_is_applicable(Location& location, std::string& path)
{
	std::string file_extension = path.substr(path.find_last_of("."));
	// check for query string
	std::vector<std::string> cgi_extensions = location.get_cgi_ext();
	int nbr_cgi_extensions = cgi_extensions.size();
	for (int i = 0; i < nbr_cgi_extensions; i++)
		if (cgi_extensions[i] == file_extension)
			return true;
	return false;
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
	res._tmp_file_path = file_path;
	file.close();
	res._status_code = "200";
	set_content_type_and_length(req, res, file_path);
	set_response_headers(req, res);
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

bool check_for_index_file(Request& req, Location& location, std::string& resource, Response& res)
{
	std::vector<std::string> index_files = location.get_index();
	if (!index_files.empty())
	{
		int nbr_indexes = index_files.size();
		for (int i = 0; i < nbr_indexes; i++)
		{
			std::string index_file_path = resource + index_files[i];
			int index_code = check_if_entity_exists(index_file_path);
			std::cout << "index_code : "<< index_code << std::endl;
			if (!index_code)
				continue;
			if (index_code == FILECODE && access(index_file_path.c_str(), R_OK) == 0)
			{
				// check if location has cgi
				res._body_path = index_file_path;
				res._status_code = "200";
				set_content_type_and_length(req, res, index_file_path);
				set_response_headers(req, res);
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
	bool index_file = check_for_index_file(req, location, resource, res);
	std::cout << "index_file: " << index_file << std::endl;
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
				// res._status_code = "301";
				// redirect_response(res._status_code, directory, req, res);
				// return REDIRECTCODE;
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

int requested_resource_by_post(std::string& resource, Location& location, Request& req, Response& res)
{
	struct stat st;
	if (stat(resource.c_str(), &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			if (resource.back() != '/')
			{
				resource += "/";
				// res._status_code = "301";
				// redirect_response(res._status_code, resource, req, res);
				// return REDIRECTCODE;
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

void requested_resource_by_error_page(std::string& error_page_path, Location& error_location, Response& res)
{
	struct stat st;
	if (stat(error_page_path.c_str(), &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			throw Response::ForbiddenPath();
		else if (S_ISREG(st.st_mode))
		{
			if (access(error_page_path.c_str(), R_OK))
				throw Response::ForbiddenPath();
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

bool check_for_upload_directory(Response& res, Request& req, Location& location)
{
	if (!location.get_upload_directory().empty())
	{
		std::string upload_directory = location.get_root() + location.get_upload_directory();
		if (upload_directory.back() != '/')
			upload_directory += "/";
		int check_code = check_if_entity_exists(upload_directory);
		std::cout << "check_code: " << check_code << std::endl; 
		if (check_code != DIRCODE)
			throw Response::NoMatchedLocation();
		if (access(upload_directory.c_str(), W_OK))
			throw Response::ForbiddenPath();
		std::string file_name = "uploaded_file";
		MimeType mime_type;
		std::cout << req.getcontent_type() << std::endl;
		std::string file_extension = mime_type.get_extension(req.getcontent_type());
		std::cout << file_extension << std::endl;
		std::string tmp_file_name = create_tmp_file_name(upload_directory, file_name, file_extension);
		if (rename(req.get_pathbody().c_str(), tmp_file_name.c_str()))
		{
			std::cout << "rename failed" << std::endl;
			std::cout << req.get_pathbody() << " " << tmp_file_name << std::endl;
			throw Response::ForbiddenPath();
		}
		res._status_code = "201";
		res._tmp_file_path = tmp_file_name;
		set_content_type_and_length(req, res, res._tmp_file_path);
		set_response_headers(req, res);
		return true;
	}
	return false;
}

void response_to_post(Response& res, Request& req, Location& location)
{
	if (!check_for_upload_directory(res, req, location))
	{
		std::string resource = location.get_root() + req.get_requestur();
		int resource_code = requested_resource_by_post(resource, location, req, res);

		if (resource_code == REDIRECTCODE)
		return;
		if (resource_code == DIRCODE)
		{
			if (!check_for_index_file(req, location, resource, res))
				throw Response::ForbiddenPath();
		}
		else if (resource_code == FILECODE)
		{
			// check if location has cgi
			if (check_if_cgi_is_applicable(location, resource))
			{
				
			}
			else
				throw Response::ForbiddenPath();
		}
	}
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
		set_response_headers(req, res);
	}
	else if (resource_code == FILECODE)
	{
		if (remove(resource.c_str()) != 0)
			throw Response::InternalServerError();
		res._status_code = "204";
		set_response_headers(req, res);
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
		set_content_type_and_length(req, res, resource);
		set_response_headers(req, res);
	}
}

Response custom_and_default_error_pages(Request& req, Response& res, Server& server, std::string error_code)
{
	try
	{
		std::map<std::string, std::string> error_map = server.get_errors_map();
		if (error_map.find(error_code) == error_map.end())
		{
			res._status_code = error_code;
			default_error_page(res);
			return res;
		}
		std::string error_page = error_map[error_code];
		std::vector<Location> server_locations = server.get_locations();
		Location error_location = find_matched_location(error_page, server_locations);
		std::vector<std::string> allowed_methods_in_location = error_location.get_allowed_methods();
		std::string get_error_method = "GET";
		check_allowed_methods(res, get_error_method, allowed_methods_in_location);
		std::string error_page_path = error_location.get_root() + error_page;
		requested_resource_by_error_page(error_page_path, error_location, res);
		res._status_code = error_code;
		res._body_path = error_page_path;
		set_content_type_and_length(req, res, error_page_path);
		set_response_headers(req, res);
		return res;
	}
	catch (std::exception& e)
	{
		std::string second_error_code = e.what();
		std::cout << second_error_code << std::endl;
		res._status_code = second_error_code;
		default_error_page(res);
		return res;
	}
}

Response server_response(Request& req, Server& server)
{
	Response res;
	init_code_map(res);
	std::vector<std::string> methods_arr;
	methods_arr.push_back("GET");
	methods_arr.push_back("POST");
	methods_arr.push_back("DELETE");
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
			redirect_response(redirection.first, redirection.second, req, res);
			return res;
		}
		for (int i = 0; i < 3; i++)
			if (req.get_method() == methods_arr[i])
				methods_ptr[i](res, req, location);
		return res;
	}
	catch (std::exception& e)
	{
		std::string error_code = e.what();
		std::cout << error_code << std::endl;
		return custom_and_default_error_pages(req, res, server, error_code);
	}
}

