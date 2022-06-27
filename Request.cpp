#include "Request.hpp"
#include <fstream>
#include <fcntl.h>
/*
 ** ------------------------------- CONSTRUCTOR --------------------------------
 */

Request::Request()
{
	writingchar = 0;
	global = 0;
	requestcomplete = 0;
	transferchunks = false;
	chunksize = -1;
	bodylenght = 0;
	iperfect = 0;
	igottheend = false;
	thereistraansfer = 0;
	headerscopmlete = 0;
	requeststatus = 0;
	chunkcomplete = true;
	pathbody="";
	Reminder = 0;
}

Request::Request( const Request & src )
{
	*this = src;
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
	chunksize = rhs.chunksize;
	serverfd = rhs.serverfd;
	server_name = rhs.server_name;
	method = rhs.method;
	writingchar = rhs.writingchar;
	chunkcomplete = rhs.chunkcomplete;
	ipaddress = rhs.ipaddress;
	port = rhs.port;
	setsocketid = rhs.setsocketid;
	thhpversion = rhs.thhpversion;
	host = rhs.host;
	thereistraansfer = rhs.thereistraansfer;
	requestur = rhs.requestur;
	Connection = rhs.Connection;
	transferchunks = rhs.transferchunks;
	content_type = rhs.content_type;
	content_lenght = rhs.content_lenght;
	data = rhs.data;
	igottheend = rhs.igottheend;
	requestcomplete = rhs.requestcomplete;
	headerscopmlete = rhs.headerscopmlete;
	pathbody = rhs.pathbody;
	requeststatus = rhs.requeststatus;
	filediscriptor = rhs.filediscriptor;
	timeout = rhs.timeout;
	bodylenght = rhs.bodylenght;
	Reminder = rhs.Reminder;	
	global = rhs.global;
	backup = rhs.backup;
	writingchar = rhs.writingchar;
	return *this;
}

// std::ostream &			operator<<( std::ostream & o, Request const & i )
// {
// 	//o << "Value = " << i.getValue();
// 	return o;
// }


/*
 ** --------------------------------- METHODS ----------------------------------
 */
int sstoi(std::string &line)
{
	int size;
	std::stringstream ss;
        ss << line;
        ss >> size;
	return size;
}

unsigned long unsigned_stoi(std::string &line)
{
	unsigned long size;
	std::stringstream ss;
        ss  <<line;
        ss >> size;
	return size;
}

bool			Request::IsHex(const std::string& str) 
{
  return (str.find_first_not_of("0123456789abcdefABCDEF", 0) == std::string::npos);
}
void			Request::settransferstat(bool j)
{
	thereistraansfer = j;
}
bool			Request::gettransferstat()
{
	return thereistraansfer;
}
int			Request::get_connection()
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
	if (ho.find(":") != std::string::npos)
	{
		//std::cout<<ho.substr(0,ho.find(":"))<<std::endl;
		//if (ho.substr(0,ho.find(":")) == "localhost")
		//{
		//	set_ip("127.0.0.1");
		//	set_server_name("localhost");
		//}
		//else
		//{
			//set_ip(ho.substr(0,ho.find(":")));
		set_server_name(ho.substr(0,ho.find(":")));
		set_port(ho.substr(ho.find(":") + 1));
	}
}
void					Request::setconnection(std::string str)
{

	//////std::cout<<str.compare("keep-alive")<<std::endl;
	if (str.compare("keep-alive") == 0)
	{
		Connection = 1;
	}
	else
		Connection = 0;
}
//void					Request::setuser_agent(std::string *us)
//{
//	host = ho;
//}

void					Request::set_socketid(int d)
{
	setsocketid = d;
}
std::string				Request::get_ip()
{
	return ipaddress;
}
std::string				Request::get_port()
{
	return port;
}

void					Request::set_ip(std::string op)
{
	ipaddress = op;
}
void					Request::set_port(std::string op)
{
	port = op;
}
std::string 			Request::getcontentlenght()
{
	return content_lenght;
}
void					Request::setcontent_length(std::string len)
{
	//char *Str = len;
	content_lenght = len ;
}	
void					Request::setcontent_type(std::string type)
{
	content_type = type;
}
bool					Request::settransferchunks(std::string len)
{
	settransferstat(true);	
	if (len.find("chunked") == std::string::npos)
		transferchunks = false;
	else
		transferchunks = true;
	return (transferchunks);
}
bool					Request::gettransferchunks()
{
	return transferchunks;
}

std::string				Request::getrandomname()
{
	srand(time(NULL));
	std::string alpha = "abcdefghijklmnopqrstuvwxyz";
	std::string result = "";
	for (int i = 0; i<12; i++)
		result = result + alpha[rand() % alpha.size()];
	return (result);
}
void					Request::adddata(char *buffer, int c)
{
	//	data.append(buffer,c//);
	if (Reminder == 0)
	{
		Reminder = 1;
		////std::cout<<"this is the oldest data : "<<data<<std::endl;
	}
	data.append(buffer,c);
	////std::cout<<"-----------------------------------------------------"<<std::endl;
}
void					Request::setunchunkedbody()
{
	//while (!requestcomplete)
	//{
		////std::cout<<data<<std::endl;
	//	filediscriptor = open(pathbody.c_str(), O_CREAT | O_RDWR | O_APPEND, 0666);
		//////std::cout<<" size : "<<bodylenght + data.size() <<" content lentgh "<<stoi(content_lenght)<<std::endl;
		
		if ((bodylenght + data.size()) <= unsigned_stoi(content_lenght))
		{
			bodylenght += data.size();
		//	////std::cout<< "" the file discriptor "<<std::endl;
			write(filediscriptor,data.c_str(),data.size());
			data.erase();
		}
		if (bodylenght == sstoi(content_lenght))
		{
			requeststatus = 200;
			requestcomplete = 1;
			//close(filediscriptor);
			return;
			//break;
		}
		else
			requeststatus = 0;
	//	close(filediscriptor);
	//while (!requestcomplete)
	}

void					Request::setchunckedbody()
{
	unsigned long found = 0;
	std::string printstring;
	int printingnum = 0;
	backup += data;
	data.erase();
	while (1)
	{
		////std::cout<<"--------------"<<std::endl;
		//perror("error");
	if ((found = backup.find("\r\n"))!= std::string::npos)
	{
		if (chunkcomplete== true)
		{
						//	////std::cout<<backup.substr(0,found)<<std::endl;

			if (IsHex(backup.substr(0,found)) == false)
			{
				////std::cout<<"allo allo allo allo allo "<<std::endl;
				requestcomplete = 1;
				requeststatus = 400;
				chunkcomplete = 1;
				chunksize = -1;
				return;
			}
			std::istringstream iss(backup.substr(0,found));
			//////std::cout<<"backup line :"<<backup.substr(0,found)<<std::endl;
    		iss >> std::hex >> chunksize;
			if ((backup.find("\r\n") + 2) < backup.size() )
				backup  = backup.substr(found + 2);
			if (chunksize == 0)
			{
				requestcomplete = 1;
				chunkcomplete = 1;
				return;
		}
		}
		if ( chunksize != -1)
		{
			if (chunksize == 0)
			 {
				requestcomplete = true;
				chunkcomplete = true;
				return;
			}
			int t = backup.size();
			if (t >= chunksize + 2)
			{
				printingnum =  write(filediscriptor,backup.substr(0,chunksize).c_str(),chunksize);
				chunkcomplete = 1;
				if (t >= chunksize + 2)
				{
					backup = backup.substr(chunksize + 2);
				}
			}
			else
			{
				chunkcomplete = false;
			}
			if (igottheend == false)
				break;

		}
		
	//	else
	//	{
	//		//if (chunksize == 0)
	//		//{
	//			////std::cout<<"allo"<<std::endl;
	//			chunkcomplete = true;
	//			requestcomplete = true;
	//		//}
	//	}

		

	}
	else
			break;	
	}

}


void					Request::settingbody()
{
	if (method == "POST" && content_lenght.empty() == true && thereistraansfer == false)
	{
		requeststatus = 400;
	}
	else if (content_lenght.empty() == false && thereistraansfer == true)
	{
		requeststatus = 400;
	}
	else if (content_lenght.empty() == false)
	{
		setunchunkedbody();
		
	}
	else
	{
		setchunckedbody();
	}
}
int 					Request::parserequest(char *buffer, int size)
{
	//if (backup.size() > 10000)
	//{
	//	for (int i = 0; i < 1000; i++)
	//	////std::cout<<"backup > 10000" <<std::endl;
	//	
	//}
	size_t	foundplace = 0;
	int po = 0;
	std::string point = ".";
	data.append(buffer, size);
	if(transferchunks == true && data.find("0\r\n\r\n") != std::string::npos)
	{////std::cout<<"allo"<<std::endl;;
		igottheend = true;

	}
	
	if (!requestcomplete)
	{
		po = 1;
		if (!headerscopmlete)
		{ 
			if (data.find("0\r\n\r\n") != std::string::npos)
			{
				igottheend = true;
			}
			if ((foundplace = data.find("\r\n\r\n")) != std::string::npos)
			{
				std::string tmp;
				tmp =data.substr(0,foundplace);
				handleheaders(tmp);
				data = data.substr(foundplace + 4);
				tmp.erase();
				headerscopmlete = 1;
				if(get_method() != "POST")
				{
					////std::cout<<"surly it s port method|"<<get_method()<<"|"<<std::endl;
					requestcomplete = 1;
					return requestcomplete;
				}
			}
		}
			if (headerscopmlete && !requestcomplete)
			{
				// so here i don t need to forget about bodypath so let s start handlig without a bodyy path 
				// imagining there just "" as a path
				if (pathbody == "")
				{
					MimeType op;
					std::string   lop;
					// std::string &lop1 = content_type;
					std::string name = getrandomname() ;
				//	name += getrandomname() ;
					name +=  op.get_extension(content_type);
					pathbody = name;
				}
	
					filediscriptor = open(pathbody.c_str(), O_CREAT | O_RDWR | O_APPEND, 0666);
					////std::cout<<filediscriptor<<std::endl;
					point.erase();
					if (filediscriptor == -1)
					{
						//bad request
						requeststatus = 400;
						return requestcomplete = 1;
					}
					else if (requeststatus == 0)// if not a bad request
					{
						settingbody();
					}
				if (requestcomplete && requeststatus == 0)
				{
					requeststatus = 200;
				
				}
					close(filediscriptor);
				//after handling headers we need to check on is there is a body nd check the extension 
				//remind me of taking this one put
				//requestcomplete = 1;
			}
		}
		if (po == 0)
			{
				////std::cout<<"i m here "<<std::endl;
			}
		//printingrequestelements();

	return (requestcomplete);
}

int					Request::handleheaders(std::string data2)
{
	int count2 = 0;
	std::string tmp;
	tmp = data2.substr(0,data2.find("\r\n"));
	//if (findfirstline(tmp) != -1)
	//{
		for(size_t i = 0; i < tmp.size(); i++)
		{
			if (tmp[i] != ' ')
			{
				std::string op;
				while(tmp[i] != ' ' && i < tmp.size())
				{
					op += tmp[i];
					i++;
				}
				count2++;
				if (count2 == 1)
					setmethod(op);
				else if (count2 == 2)
					setrequest(op);
				else
					sethttpversion(op);
				op.erase();
			}
		}
		data2 = data2.substr(data2.find("\n") + 1);
		//////std::cout<<data2<<std::endl;
		size_t p = 0;
		int f = 0;
		int cc = 0;
		while (((p = data2.find("\n")) != std::string::npos || (p =  data2.find("\r\n\r\n")) != std::string::npos))
		{	//std::cout<<"|||||||||||||||||||||||||||||||||1"<<std::endl;

			if (f != 1)
			 tmp = data2.substr(0, p - 1);
			else
				tmp = data2.substr(0,p);
			cc = tmp.find(":");
				//std::cout<<"|||||||||||||||||||||||||||||||||2"<<std::endl;

			//std::ßcout<<"|"<<tmp.substr(cc + 2)<<"|"<<std::endl;	
		//	////std::cout<<cc<<std::endl;
			std::string headersfield[5] = {"Host","Connection","Content-Length","Content-Type","Transfer-Encoding"};
		//	////std::cout<<tmp.substr(0, cc ).compare(headersfield[2])<<std::endl;
		//	std::string tmp;
			std::string c = " ";
			if (tmp.substr(0,cc ).find(" ") != std::string::npos)
			{
//////std::cout<<tmp.substr(0,cc).compare(headersfield[3])<< "Tmp = " << tmp.substr(0,cc) << " header = "<< headersfield[3]<<std::endl;
				return 0;
			}
			if (tmp.substr(0, cc ).compare(headersfield[0])== 0)
			{
				sethost(tmp.substr(cc + 2));
					
			}
			if (tmp.substr(0, cc ).compare(headersfield[1])== 0)
				setconnection(tmp.substr(cc + 2));
					
			if (tmp.substr(0, cc ).compare(headersfield[2])== 0)
				{//////std::cout<<"|                 wa zaaaaaaaab ii  |"<<std::endl;	ƒ
				setcontent_length(tmp.substr(cc + 2));}
			if (tmp.substr(0, cc ).compare(headersfield[3])== 0)
				setcontent_type(tmp.substr(cc + 2));
			if (tmp.substr(0, cc ).compare(headersfield[4])== 0)
				settransferchunks(tmp.substr(cc + 2));
			if (f != 1)
				data2 = data2.substr(p + 1);
				

			else
			{
				//std::cout<<"|||||||||||||||||||||||||||||||||3"<<std::endl;
				break;
			}
			//std::cout<<"|||||||||||||||||||||||||||||||||4"<<std::endl;
			if (data2.find("\n") == std::string::npos)
			{
				f = 1;
				data2 += "\n";
			} 
		}   
	//}
	return 1;
}

void			Request::printingrequestelements()
{
	////std::cout<<"Method            : "<<get_method()<<std::endl;
	////std::cout<<"Request UR        : "<<requestur<<std::endl;
	////std::cout<<"HOST              : "<<gethost()<<std::endl;
	////std::cout<<"Content Type      : "<<content_type<<std::endl;
	////std::cout<<"Content length    : "<<content_lenght<<std::endl;
	////std::cout<<"Connection        : "<<Connection<<std::endl;
	////std::cout<<"Socketfd          : "<<setsocketid<<std::endl;
	////std::cout<<"pathbody          : "<<pathbody<<std::endl;
	////std::cout<<"request complete  : "<<requestcomplete<<std::endl;
	////std::cout<<"did i got the end : "<<	igottheend<<std::endl;
	////std::cout<<"headers complete  : "<<headerscopmlete<<std::endl;
//	if (chunkcomplete == false)
//	
	if(chunksize != -1)
	{
	//	for (int i= 0; i < 50;i++ )
	//	{
	//////std::cout<<"============================================================================================================="<<std::endl;
	//	}
	//		sleep(10);

	}
	//////std::cout<<"chunksize  : "<<chunksize<<std::endl;

	////std::cout<<"chunked complete  : "<<chunkcomplete<<std::endl;
	////std::cout<<"iperfect : "<<iperfect<<std::endl;
	iperfect++;
}


/* --------------------------------- ACCESSOR ---------------------------------*/



/* ************************************************************************** */
