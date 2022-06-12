#include <iostream>
#include <cstring>
#include <vector>
#include <exception>
#include <fstream>
#include <ctime>

using namespace std;

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

int main()
{
	vector<string> entities;
	entities.push_back("home");
	entities.push_back("tmp");
	entities.push_back("urs");
	entities.push_back("etc");
	entities.push_back("local");

	std::string file_path = "autoindex.html";
	std::ofstream file;
	file.open(file_path);
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>Index of " << "/Desktop/" << "</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<h1>Index of "<< "/Desktop/" <<"</h1>\n";
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
	//res._body_path = file_path;
	file.close();

	cout << set_date_header() << endl;
}