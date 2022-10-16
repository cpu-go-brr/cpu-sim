#pragma once

#include "requests.hpp"

#include <iostream>
#include <map>
#include <regex>

#include "../include/intel4004.hpp"

class Server
{
	public:
		Server(int port, Intel4004* cpu);
		~Server();
		void start();
		void run();
		void stop();
		void sendError(int socket, std::string error);
		static std::string URLDecode(std::string url);
	private:
		void init();

		void handleGetRequest(int socket, std::string request);

		const int port;
        bool isRunning;
        Intel4004* cpu;
		std::map<std::string, resourcefunction> resources;
};
