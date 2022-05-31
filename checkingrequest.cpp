#include <webser.hpp>

bool checkingrequest(Request req)
{
    bool itis;
    std::string URIcarach = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ._~:/?#[]@!$&'()*+,;=%";
    if (req.gettransferstat() == true &&  req.gettransferchunks() == false)
    {
        //Method not implemented 501 if => Transfer-Encoding header exist and is different to “chunked”
        return false;
    }
    if (req.gettransferstat() == false && req.getcontentlenght().empty()== 0 && req.get_method() == "POST")
    {
        //Bad Request 400 if => Transfer-Encoding not exist Content-Length not exist The method is Post
        return false;
    }
    for (int i = 0; i < req.get_requestur().length(); i++)
    {
        for (int j = 0; j < URIcarach.length(); j++)
        {
            if (req.get_requestur()[i] == URIcarach[j])
            {
                itis = true;
            }
        }
        if (itis == false)
        {
            //400 bad request if => Request uri contain a character not allowded
            return ;
        }
    }
    if (req.get_requestur().length() > 2048)
    { 
        // 414 Request-URI Too Long
            return;
    }
    if (int i = 1)//checking client body max 
    {
        //if => Request body larger than client max body size in config file
        return;
    }
}