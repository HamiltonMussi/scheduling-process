#ifndef RRQUEUE_H
#define RRQUEUE_H

#include "process.h"
#include <queue>

using namespace std;

class RRQueue {
    public:
        RRQueue(int quantum);
        std::queue<Process> queue;
        int quantum;
};

RRQueue::RRQueue(int quantum) {
    this->quantum =  quantum;
}

#endif