#include <iostream>
#include <cstring>
#include <vector>
#include <exception>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
using namespace std;

#define FILECODE 1
#define DIRCODE 2

// class Location {
// 	public:
// 		std::string path;
// 		Location() {path = "";}
// 		Location(std::string path) {this->path = path;}
//         Location(const Location &src) {this->path = src.path;}
//         ~Location() {}
//         Location &operator=( Location const & rhs ) {if (this != &rhs) {this->path = rhs.path;} return *this;}

// 		class NoMatchedLocation : public std::exception
// 		{
// 			public:
// 			virtual const char* what() const throw()
// 			{
// 				return "404";
// 			}
// 		};
// }; 

// Location get_matched_location(std::string path, std::vector<Location>& locations)
// {
// 	if (path != "")
// 	{
// 		int nbr_locations = locations.size();
// 		for (int i = 0; i < nbr_locations; i++)
// 		{
// 			if (locations[i].path == path)
// 			{
// 				return locations[i];
// 			}
// 		}
// 		size_t found = path.find_last_of("/");
// 		if (found != std::string::npos)
// 		{
// 			std::string path_without_last_slash = path.substr(0, found);
// 			return get_matched_location(path_without_last_slash, locations);
// 		}
// 	}
// 	throw Location::NoMatchedLocation();
// }

// int main()
// {
// 	std::vector<Location> locations;
// 	locations.push_back(Location("/"));
// 	locations.push_back(Location("/home/site"));
// 	locations.push_back(Location("/home/site/about"));
// 	locations.push_back(Location("/home/site/contact"));
// 	locations.push_back(Location("/home/site/contact/me"));
// 	locations.push_back(Location("/home/site/contact/me/now"));
// 	try
// 	{
// 		Location matched_location = get_matched_location("", locations);
// 		cout << matched_location.path << endl;
// 	}
// 	catch(const Location::NoMatchedLocation& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
	
	
// 	return 0;
// }

std::string set_date_header()
{
	time_t ttime = time(0);
    char* dt = ctime(&ttime);
	string date = string(dt);
	return (date.substr(0, date.size() - 1));
}

// int main()
// {
// 	vector<string> entities;
// 	entities.push_back("home");
// 	entities.push_back("tmp");
// 	entities.push_back("urs");
// 	entities.push_back("etc");
// 	entities.push_back("local");

// 	std::string file_path = "autoindex.html";
// 	std::ofstream file;
// 	file.open(file_path);
// 	file << "<!DOCTYPE html>\n";
// 	file << "<html>\n";
// 	file << "<head>\n";
// 	file << "<title>Index of " << "/Desktop/" << "</title>\n";
// 	file << "</head>\n";
// 	file << "<body>\n";
// 	file << "<h1>Index of "<< "/Desktop/" <<"</h1>\n";
// 	file << "<hr>\n";
// 	file << "<pre>\n";
// 	file << "<a href=" << "../" << ">../</a>\n";
// 	for (int i = 0; i < entities.size(); i++)
// 	{
// 		file << "<a href=\"" << entities[i] << "\">" << entities[i] << "</a>\n";
// 	}
// 	file << "</pre>\n";
// 	file << "<hr>\n";
// 	file << "</body>\n";
// 	file << "</html>\n";
// 	//res._body_path = file_path;
// 	file.close();

// 	cout << set_date_header() << endl;
// }


// class Beeg {
// 	public:
// 	class BeegBoi : public std::exception
// 	{
// 		public:
// 		virtual const char* what() const throw()
// 		{
// 			return "BOIIII";
// 		}
// 	};
// 	class BeegGal : public std::exception
// 	{
// 		public:
// 		virtual const char* what() const throw()
// 		{
// 			return "GAAAAAL";
// 		}
// 	};
// };

// int BeegBorgir(int a)
// {
// 	if (a % 2)
// 	{
// 		throw Beeg::BeegBoi();
// 	}
// 	return a / 2;
// }

// int testBeeg(int b)
// {
// 	if (BeegBorgir(b) < b)
// 	{
// 		cout << "here" << endl;
// 		return 2;
// 	}
// 	else
// 		return 1;
// }


// int main()
// {
// 	try{
// 		int i = testBeeg(5);
// 	}
// 	catch(exception& e)
// 	{
// 		cout << e.what() << endl;
// 	}
// }

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

// int delete_directory(std::string& path)
// {
// 	DIR* dir;
// 	struct dirent* entry;
// 	if ((dir = opendir(path.c_str())) != NULL)
// 	{
// 		while ((entry = readdir(dir)) != NULL)
// 		{
// 			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
// 			{
// 				if (path.back() != '/')
// 					path += "/";
// 				std::string new_path = path + string(entry->d_name);
// 				int entity_type = check_if_entity_exists(new_path);
// 				if (entity_type == DIRCODE)
// 				{
// 					if (delete_directory(new_path))
// 					{
// 						cerr << "Error deleting directory " << new_path << endl;
// 						return 1;
// 					}
// 					else
// 						cerr << "deleted directory " << new_path << endl;
// 				}
// 				else if (entity_type == FILECODE)
// 				{
// 					if (remove(new_path.c_str()) != 0)
// 					{
// 						cerr << "Error deleting file " << new_path << endl;
// 						return 1;
// 					}
// 					else
// 						cerr << "deleted file " << new_path << endl;
// 				}
// 			}
// 		}
// 		if (rmdir(path.c_str()))
// 			cerr << "Error deleting directory " << path << endl;
// 		cerr << "deleted directory " << path << endl;
// 		closedir(dir);
// 		return 0;
// 	}
// 	return 1;
// }


int foofoo(int n)
{
	if (n == 0)
		return 0;
	else if (n == 2)
		throw "error";
	else
	{
		cout << n << endl;
		return foofoo(n - 1);
	}
}

std::string create_temporary_file(std::string& path, std::string& file_name, std::string& extension)
{
	time_t time_since1970;
  	time_since1970 = time(NULL);
	std::stringstream ss;
	ss << time_since1970;
	string time_since1970_string = ss.str();
	std::string tmp_file_path = path + time_since1970_string + "_" + file_name + extension;
	std::ofstream tmp_file(tmp_file_path.c_str());
	tmp_file.close();
	return tmp_file_path;
}

std::string remove_query_string(std::string str)
{
	std::cout << "str: " << str << std::endl; 
	std::string::size_type pos = str.find('?');
	if (pos != std::string::npos)
	{
		str = str.substr(0, pos);
	}
	std::cout << "str: " << str << std::endl;
	return str;
}

int main()
{
	// std::string path = "/Users/hmahjour/Desktop/CPP_pool/";
	std::string file_name = "/Users/hmahjour/Desktop/CPP_pool/?toberenamed.txt";
	// std::string extension = ".txt";
	// std::string tmp_file_path = create_temporary_file(path, file_name, extension);
	std::string new_file_path = "/Users/hmahjour/Desktop/cotest/renamedfile.txt";
	std::string str = remove_query_string(file_name);
	// if (rename(file_name.c_str(), new_file_path.c_str()))
	// 	cout << "failed to rename file" << endl;
	// else
	// 	cout << "renamed file successfully" << endl;
		// std::ofstream tmp_file(tmp_file_path.c_str());
		// tmp_file << "Hello World!";
	//tmp_file.close();
	return 0;
}