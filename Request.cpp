#include "Request.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Request::Request()
{
}

Request::Request( const Request & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Request::~Request()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Request &				Request::operator=( Request const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Request const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/
bool			Request::get_connection()
{
	return Connection;
}
std::string			Request::gethost()
{
	return host;
}
std::string				Request::get_requestur()
{
	return requestur;
}
std::string				Request::get_httpversion()
{
	return	thhpversion;
}
std::string				Request::get_method()
{
	return method;
}

void					Request::setmethod(std::string me)
{
	method = me;
}
void					Request::sethttpversion(std::string me)
{
	thhpversion = me;
}
void					Request::setrequest(std::string me)
{
	requestur = me;
}
void					Request::sethost(std::string ho)
{
	host = ho;
}
void					Request::setconnection(std::string str)
{
	std::cout <<"|"<<str<<"|"<<std::endl;
//	std::cout<<"|"<<
	std::cout<<str.compare("keep-alive")<<std::endl;
	if (str == "keep-alive")
	{
	Connection = true;
		std::cout <<"im here "<<str<<std::endl;

	}
	if (str == "close")
	Connection = false;
}
//void					Request::setuser_agent(std::string *us)
//{
//	host = ho;
//}
void					Request::setcontent_length(std::string len)
{
	//char *Str = len;
	content_lenght = stoi(len);
}	
void					Request::setcontent_type(std::string type)
{
	content_type = type;
}
bool					Request::settransferchunks(std::string len)
{		
		if (len == "chunk")
		transferchunks = true;
		else 
		transferchunks = false;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */