#include <iostream>
#include <cstring>
#include <vector>
#include <exception>
using namespace std;

class Location {
	public:
		std::string path;
		Location() {path = "";}
		Location(std::string path) {this->path = path;}
        Location(const Location &src) {this->path = src.path;}
        ~Location() {}
        Location &operator=( Location const & rhs ) {if (this != &rhs) {this->path = rhs.path;} return *this;}

		class NoMatchedLocation : public std::exception
		{
			public:
			virtual const char* what() const throw()
			{
				return "404";
			}
		};
}; 

Location get_matched_location(std::string path, std::vector<Location>& locations)
{
	if (path != "")
	{
		int nbr_locations = locations.size();
		for (int i = 0; i < nbr_locations; i++)
		{
			if (locations[i].path == path)
			{
				return locations[i];
			}
		}
		size_t found = path.find_last_of("/");
		if (found != std::string::npos)
		{
			std::string path_without_last_slash = path.substr(0, found);
			return get_matched_location(path_without_last_slash, locations);
		}
	}
	throw Location::NoMatchedLocation();
}

int main()
{
	std::vector<Location> locations;
	locations.push_back(Location("/"));
	locations.push_back(Location("/home/site"));
	locations.push_back(Location("/home/site/about"));
	locations.push_back(Location("/home/site/contact"));
	locations.push_back(Location("/home/site/contact/me"));
	locations.push_back(Location("/home/site/contact/me/now"));
	try
	{
		Location matched_location = get_matched_location("", locations);
		cout << matched_location.path << endl;
	}
	catch(const Location::NoMatchedLocation& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
	return 0;
}