#pragma once

#include "intel4004.hpp"
#include <string>
#include <map>

typedef struct resourcefunctionparameter
{
    int socket;
    std::string request;
    Intel4004* cpu;
} resourcefunctionparameter;

typedef bool (*resourcefunction)(resourcefunctionparameter);


static std::string header = "HTTP/1.1 200\r\nContent-Type: text/html; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nConnection: close\r\n\r\n ";
static std::string jsonheader = "HTTP/1.1 200\r\nContent-Type: application/json; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nConnection: close\r\n\r\n ";


void reply(int socket, std::string reply);
bool greet(resourcefunctionparameter p);
bool view(resourcefunctionparameter p);