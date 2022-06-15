#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>
# include <stdlib.h>

class Request
{

	public:

		Request();
		Request( Request const & src );
		~Request();
		Request &		operator=( Request const & rhs );
		void setmethod(std::string me);
		void sethost(std::string ho);
		void setconnection(std::string str);
		void setaccept_enco(std::string *enc);
		bool settransferchunks(std::string ther);
		void setcontent_length(std::string len);
		void setcontent_type(std::string type);
		void sethttpversion(std::string stri);
		bool gettransferchunks();
		std::string get_requestur();
		void setrequest(std::string str);
		std::string get_httpversion();
		std::string get_method();
		std::string gethost();
		std::string get_port();
		std::string get_ip();
		std::string getcontentlenght();
		bool gettransferstat();
		void settransferstat(bool j);
		void set_ip(std::string);
		void set_port(std::string);
		bool get_connection();
		void set_socketid(int fd);
		int	 get_socketid();
		char *accept_encoding();

	private:
		std::string method;
		std::string ipaddress;
		std::string port;
		int setsocketid;
		std::string thhpversion;
		std::string host;
		bool thereistraansfer;
		std::string requestur;
		bool Connection;
		bool transferchunks;
		std::string content_type;
		std::string  content_lenght;
		//std::string *user_agent;
		//std::string *Accept_encoding;
		


}; 

std::ostream &			operator<<( std::ostream & o, Request const & i );

#endif /* ********************************************************* REQUEST_H */