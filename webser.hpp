#ifndef WEB_SERVER
#define WEB_SERVER
#include <string>
#include<iostream>
#include <Request.hpp>
#include <specifications.hpp>
#include <vector>
#include <server.hpp>
typedef struct stru{
    std::string user;
    int approval;
    int version;
    stru *next;

}           t_str;
t_str


void checking(Request req);

#endif 