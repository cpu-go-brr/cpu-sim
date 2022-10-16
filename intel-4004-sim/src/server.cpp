#include "../include/server.hpp"
#include "../include/requests.hpp"
#include <unistd.h>
#include <thread>
#include <sys/socket.h>

#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

Server::Server(int port, Intel4004* cpu) : port(port), isRunning(false), cpu{cpu}
{
    init();
}
Server::~Server()
{
    stop();
}

void Server::init()
{
    resources["/greet"] = greet;
    resources["/view"] = view;
}

void Server::start()
{
    if (isRunning)
        return;
    isRunning = true;
    run();
}

void Server::run()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket creation failed...\n");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));

    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        perror("socket bind failed...\n");
        printf("%s\n",strerror(errno));

        exit(0);
    }

    while (isRunning)
    {
        // Now server is ready to listen and verification
        if ((listen(sockfd, 5)) != 0)
        {
            perror("Listen failed...\n");
            exit(0);
        }
        len = sizeof(cli);

        // Accept the data packet from client and verification
        connfd = accept(sockfd, (struct sockaddr *)&cli, (socklen_t*)&len);
        if (connfd < 0)
        {
            printf("server accept failed...\n");
            exit(0);
        }

        const int requestbuffsize = 1 << 10;
        char buffer[requestbuffsize];

        std::string request = "";    
        size_t size;
        do
        {
            size = read(connfd, &buffer, requestbuffsize-1);
            request += std::string(buffer, size);
        } while (size >= requestbuffsize-1);
        
        // std::cout << "(" << request << ")" << std::endl;

        size_t request_end = request.find(' ');
        if (request.substr(0, request_end) == "GET")
        {
            handleGetRequest(connfd, request);
        }
    }
}

void Server::stop()
{
    isRunning = false;
}

void Server::handleGetRequest(int socket, std::string request)
{

    size_t type_end = request.find(' ') + 1;
    size_t command_end = request.find(' ', type_end + 1);
    std::string command = request.substr(type_end, command_end - type_end);

    size_t begin_param = command.find('?');
    if (begin_param != std::string::npos)
    {
        command = command.substr(0, begin_param);
    }

    if (!resources.contains(command))
    { // unknown command
        sendError(socket, "unknown resource");
        close(socket);
        return;
    }

    std::thread([=, this]()
                {
resourcefunctionparameter p;
p.socket = socket;
p.request = request;
p.cpu = cpu;
        resources[command](p);
        close(socket); })
        .detach();
}

// sending error to socket
void Server::sendError(int socket, std::string error)
{
    reply(socket, header + error);
}

std::string Server::URLDecode(std::string url)
{
    std::replace(url.begin(), url.end(), '+', ' ');

    std::string result;
    char ch;
    unsigned int i, ii;
    for (i = 0; i < url.length(); i++)
    {
        if (int(url[i]) == '%')
        {
            sscanf(url.substr(i + 1, 2).c_str(), "%x", &ii);

            ch = static_cast<char>(ii);
            result += ch;

            i += 2;
        }
        else
        {
            result += url[i];
        }
    }
    return (result);
}
