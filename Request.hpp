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
		std::string server_name;
		std::string get_server_name()
		{
			return server_name;
		}
		void set_server_name(std::string name)
		{
			 server_name = name;
		}
		std::string get_ip();
		std::string getcontentlenght();
		std::string	get_pathbody()
		{
			return pathbody;
		}
		bool gettransferstat();
		void settransferstat(bool j);
		void set_ip(std::string);
		void set_port(std::string);
		int get_connection();
		std::string getcontent_type()
		{
			return content_type;
		}
		void set_socketid(int fd);
		void set_timeout(long int op){
			timeout = op;
		}
		void setserver_fd(int a )
		{
			serverfd = a;
		}
		int getserver_fd()
		{
			return serverfd;
		}
		long int get_timeout()
		{
			return timeout;
		}
		int	 get_socketid();
		bool get_requestiscomplete()
		{
			return requestcomplete;
		}
		int parserequest(char *buffer, int size);
		char *accept_encoding();
		int handleheaders(std::string data2);
		void setunchunkedbody();
		void setchunckedbody();
		bool IsHex(const std::string& str);
		int iperfect;
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
		long int timeout;
		std::string backup;
		size_t writingchar;
		bool igottheend;
		int chunksize;
		int global;
		bool chunkcomplete;
		int serverfd;
		int Reminder;
		//this attribut it s about (content L and Tran E )
		//std::string *Accept_encoding;
		


}; 

int  findfirstline(std::string data);
// std::ostream &			operator<<( std::ostream & o, Request const & i );

#endif /* ********************************************************* REQUEST_H */