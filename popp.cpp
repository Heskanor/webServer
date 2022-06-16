#include "webser.hpp"
int main()
{
    MimeType op;
    std::string allop;
    allop =+ "text/html";
    std::string &allo =allop;
    std::cout<<op.get_extension("text/html")<<std::endl;
}