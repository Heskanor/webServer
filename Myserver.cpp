#include "Myserver.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Myserver::Myserver()
{
}

Myserver::Myserver( const Myserver & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Myserver::~Myserver()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Myserver &				Myserver::operator=( Myserver const & rhs )
{
	port = rhs.port;
	ipaddress = rhs.ipaddress;
	fd = rhs.fd;
	address = rhs.address;
	addrlen = rhs.addrlen;
	index = rhs.index;
	return *this;
}

// std::ostream &			operator<<( std::ostream & o)
// {
// 	//o << "Value = " << i.getValue();
// 	return o;
// }


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */