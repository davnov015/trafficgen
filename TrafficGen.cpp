//
// Created by davidb on 7/14/21.
//

#include "TrafficGen.h"
#include <thread>
#include <cstring>
#include <iostream>
#include <chrono>

using namespace std::chrono;

TrafficGen::TrafficGen(const char* ipv4, const char* ipv4Interface, in_port_t sourcePort, in_port_t targetPort,
                       time_t timeInterval)
        : socket(sourcePort, to_addr(ipv4Interface)) {
    sockaddr_in target = {};
    target.sin_addr = to_addr(ipv4);
    target.sin_port = htons(targetPort);
    target.sin_family = AF;
    this->target = target;
    std::string addrTxt = to_string(this->target.sin_addr);
    interval = timeInterval;
    running = false;
}

void TrafficGen::start(uint16_t threadCount) {
    running = true;
    for (uint16_t i = 0; i < threadCount; ++i){
        std::thread senderThread(&TrafficGen::generateTraffic, this);
        senderThread.detach();
    }
}

void TrafficGen::stop() {
    running = false;
}

bool TrafficGen::isRunning() const noexcept {
    return running;
}

void TrafficGen::generateTraffic() {
    static const size_t DATA_LENGTH = 1024 * 63;
    const byte dataBlock[DATA_LENGTH] = {"TEST"};
    try {
        auto startTime = std::chrono::steady_clock::now();
        while (running){
            socket.sendto(dataBlock, DATA_LENGTH, target);
            auto currentTime = steady_clock::now();
            time_t timeElapsed = duration_cast<seconds>(currentTime - startTime).count();
            running = timeElapsed < interval && running;
        }
        socket.shutdown();
    }
    catch (std::invalid_argument& error){
        std::cout << error.what() << std::endl;
        running = false;
    }
    catch (std::exception& error){
        std::cout << error.what() << std::endl;
    }
}
