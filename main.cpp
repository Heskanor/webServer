
 #include "Webserver.hpp"  
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include "Request.hpp"
#include <stdlib.h>
#include <sys/select.h>
#include <fcntl.h>
#include <map>
#define PORT 7799
#define BUFFERSIZE 2048


int readpo = 0;
int  findfirstline(std::string data)
{
	std::string stringg[9];
	stringg[0] ="GET";
	stringg[1] ="POST";
	stringg[2] ="DELETE";

	std::string tmp;
	tmp = data.substr(0,data.find(" "));
	//////std::cout<<tmp<<std::endl;

	for (int i = 0; i <= 2 ; i++)
	{
			if (tmp.find(stringg[i]) == 0)
			{
				return i;
			}
	}
	tmp.erase();
	return(-1);
}


int main(int argc, char **argv){

	if (argc == 2)
	 {
		signal(SIGPIPE,SIG_IGN);
		std::string lop;
		lop.append(argv[1]);
		Webserver op(lop);
		op.webservbuild();
		op.Runmywebserver();
	 }

	std::cout<<"Number of (ARGS) not Correct"<<std::endl;
	
	}
