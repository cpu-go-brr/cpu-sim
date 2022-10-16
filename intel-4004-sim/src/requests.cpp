#include "../include/requests.hpp"

#include <unistd.h>
#include <regex>

void reply(int socket, std::string reply)
{
    write(socket, reply.c_str(), reply.size());
}

bool greet(resourcefunctionparameter p)
{
	reply(p.socket, header + "HI :)");
	return true;
}


bool view(resourcefunctionparameter p)
{
    std::string css = "<style>* {\
  font-family:monospace;\
}</style>";
    reply(p.socket, header + css + std::regex_replace(std::regex_replace(p.cpu->get_status(), std::regex("\n"), "<br>"), std::regex(" "),"&nbsp;"));
	return true;
}