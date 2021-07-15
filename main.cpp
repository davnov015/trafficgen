#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <signal.h>
#include <memory>
#include "TrafficGen.h"

using namespace std::chrono;

std::unique_ptr<TrafficGen> trafficGen;

void printHelp(){
    std::cout << "Copyright (c) David Bozhanov" << std::endl;
    std::cout << "Usage: trafficgen <IPv4 Interface> <Source Port> <IPv4 Target> <Target Port> <Duration (seconds)> <Thread Count (optional, default 1)>" << std::endl;
}

void run(const char* ipv4Interface, const char* sourcePort, const char* ipv4, const char* targetPort, const char* timeInterval, const char* threadCount = nullptr){
	try{
		uint16_t tc = threadCount? std::stoi(threadCount) : 1;
		trafficGen = std::make_unique<TrafficGen>(ipv4, ipv4Interface, std::stoi(sourcePort), std::stoi(targetPort), std::stoi(timeInterval));
		trafficGen->start(tc);
	} catch (std::exception& error){
		std::cout << error.what() << std::endl;
		trafficGen->stop();
		return;
	}
	signal(SIGINT, [](int signal){
		trafficGen->stop();
	});
	while (trafficGen->isRunning()){
		std::cout << "Running..." << std::endl;
		std::this_thread::sleep_for(1s);
	}
}

int main(int argc, const char** argv) {
    if (argc == 6){
        run(argv[1], argv[2], argv[3], argv[4], argv[5]);
    } else if (argc == 7){
	    run(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
    } else if (argc == 2 && strcmp(argv[1], "--help") == 0){
        printHelp();
    } else
        printHelp();
    return 0;
}
