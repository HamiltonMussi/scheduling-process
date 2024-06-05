#ifndef PROCESS_H
#define PROCESS_H

#include <queue>
#include "io.h"

using namespace std;

class Process {
    public:
        Process() {};
        Process(int id, int burst, int ioCount); 
        int id;
        int burst;
        int ioCount;
        int remainingBurst;
        int waitingTime;
        std::queue<IO> ioQueue;
};

Process::Process(int id, int burst, int ioCount){
    this->id = id;
    this->burst = burst;
    this->ioCount = ioCount;
    this->remainingBurst = burst;
    this->waitingTime = 0;

    std::queue<IO> ioQueue;
    for (int i = 0; i <= ioCount; i++) {
        IO ioElement;
        ioQueue.push(ioElement);
    }

    this->ioQueue = ioQueue; 
}

#endif