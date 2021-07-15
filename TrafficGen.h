//
// Created by davidb on 7/14/21.
//

#ifndef TRAFFICGEN_TRAFFICGEN_H
#define TRAFFICGEN_TRAFFICGEN_H

#include "Common.h"
#include "UDPSocket.h"
#include <atomic>

class TrafficGen {
public:
    TrafficGen() = delete;
    TrafficGen(const char* ipv4, const char* ipv4Interface, in_port_t sourcePort, in_port_t targetPort,
               time_t timeInterval);
    TrafficGen(const TrafficGen&) = delete;
    ~TrafficGen() = default;

    void start(uint16_t threadCount);
    void stop();

    bool isRunning() const noexcept;

    TrafficGen& operator=(const TrafficGen&) = delete;

private:
    UDPSocket socket;
    sockaddr_in target;
    time_t interval;
    std::atomic_bool running;

    void generateTraffic();
};


#endif //TRAFFICGEN_TRAFFICGEN_H
