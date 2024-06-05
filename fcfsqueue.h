#ifndef FCFSQUEUE_H
#define FCFSQUEUE_H

#include "process.h"
#include <queue>

using namespace std;

class FCFSQueue {
    public: 
        std::queue<Process> queue;
};

#endif