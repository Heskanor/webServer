#include "webser.hpp"
  
int checkingservers(std::vector<Server> lop, Request req)
{
    std::vector<int> op;
    int i =0;
    int size = 0;
    int storingi = -1;
    for (int i = 0; i < lop.size();i++)
    {
        std::cout<<lop[i].get_listenAddress()<<std::endl;
    }
    for (int i = 0;i < lop.size();i++)
    {
        if (lop[i].get_listenAddress() == req.get_ip() && std::to_string(lop[i].get_listenPort()) == req.get_port())
        {
            std::cout<<"----"<<i<<"---"<<std::endl;
            std::cout<<lop[i].get_listenAddress()<<std::endl;
            std::cout<<lop[i].get_listenPort()<<std::endl;
            std::cout<<req.get_port()<<std::endl;
            std::cout<< req.get_ip()<<std::endl;
            op.push_back(i);
        }
    }
    if (op.empty() == false)
    {
        for (int i = 0; i < op.size(); i++)
        {
            for (int j = 0; j < lop.size(); j++)
            {
                if (op[i] == j)
                {
                    if (lop[i].get_server_name() == req.get_ip())
                    {
                        return op[i];
                    }
                }
            }
        }   

    }
    return -1;
}
int chekingrequest(Request req)
{
    int itis;
    int f = false;
    int t = true;
    std::string URIcarach = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ._~:/?#[]@!$&'()*+,;=%";
    if (req.gettransferstat() == 1 &&  req.gettransferchunks() == 0)
    {
        //Method not implemented 501 if => Transfer-Encoding header exist and is different to “chunked”
        std::cout<<"im hereee 1"<<std::endl;
        return 0;
    }
    if (req.gettransferstat() == 0 && req.getcontentlenght().empty()== 0 && req.get_method() == "POST")
    {
        //Bad Request 400 if => Transfer-Encoding not exist Content-Length not exist The method is Post
         std::cout<<"im hereee 2"<<std::endl;
        return 400;
    }
    for (int i = 0; i < req.get_requestur().length(); i++)
    {
        for (int j = 0; j < URIcarach.length(); j++)
        {
            if (req.get_requestur()[i] == URIcarach[j])
            {
                itis = 1;
            }
        }
        if (itis == 0)
        {
             std::cout<<"im hereee 3"<<std::endl;
            //400 bad request if => Request uri contain a character not allowded
            return 400;
        }
    }
    if (req.get_requestur().length() > 2048)
    { 
        // 414 Request-URI Too Long
         std::cout<<"im hereee 4"<<std::endl;
            return 414;
    }
    int i = 1;
    if (i == 1)//checking client body max 
    {
        //if => Request body larger than client max body size in config file
         std::cout<<"im hereee 5"<<std::endl;
        return 0;
    }
    return 1;
}
int main() {
    std::vector<Server> lop;
    Server ser1;
    Server ser2;
    Server ser3;
    Request req;

    req.set_ip("120.0.0.1");
    req.set_port("80");
   // std::cout<<"holla : "<< req.get_port()<<std::endl;
    ser1.set_listenPort("80");
    ser3.set_listenPort("80");
    ser2.set_listenPort("80");
    ser1.set_listenAddress("120.0.0.6");
    ser2.set_listenAddress("120.0.0.1");
    ser3.set_listenAddress("120.0.0.3");
    ser1.set_server_name("120.0.0.1");
    ser2.set_server_name("120.0.0.1");
    ser3.set_server_name("120.0.0.3");
    lop.push_back(ser1);
    lop.push_back(ser2);
    lop.push_back(ser3);
   std::cout<<checkingservers(lop,req)<<std::endl;

    //std::cout <<checkingservers(lop,req)<<std::endl;
    



}