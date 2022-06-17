#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>
# include <stdlib.h>
# include "webser.hpp"
class Request
{

	public:

		Request();
		Request( Request const & src );
		~Request();
		Request &		operator=( Request const & rhs );
		void settingbody();
		void printingrequestelements();
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
		int get_connection();
		void set_socketid(int fd);
		int	 get_socketid();
		int parserequest(char *buffer, int size);
		char *accept_encoding();
		int handleheaders(std::string data2);
		void setunchunkedbody();
		void setchunckedbody();
	//	void settingbody();
		std::string	getrandomname();
		void adddata(char *buffer, int c);
	private:
		std::string method;
		std::string ipaddress;
		std::string port;
		int setsocketid;
		std::string thhpversion;
		std::string host;
		bool thereistraansfer;
		std::string requestur;
		int Connection;
		bool transferchunks;
		std::string content_type;
		std::string  content_lenght;
		std::string data;
		bool requestcomplete;
		bool headerscopmlete;
		std::string pathbody;
		int requeststatus;
		int filediscriptor;
		int bodylenght;
		std::string backup;
		size_t writingchar;
		int chunksize;
		bool chunkcomplete;
		int Reminder;
		//this attribut it s about (content L and Tran E )
		//std::string *Accept_encoding;
		


}; 

int  findfirstline(std::string data);
std::ostream &			operator<<( std::ostream & o, Request const & i );

#endif /* ********************************************************* REQUEST_H */