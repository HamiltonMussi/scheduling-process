#include <iostream>
#include "process.h"
#include "rrqueue.h"
#include "fcfsqueue.h"
#include "io.h"

using namespace std;

#define MAX_WAITING_TIME 30
#define IO_DURATION 20

int main() {
    Process p0(1, 50, 1);
    Process p1(2, 20, 2);
    RRQueue q0(10);
    FCFSQueue q1;

    int timeCounter = 0;
    bool poppedIOp0;
    bool poppedIOp1;
    int remainingQuantum = q0.quantum;
    Process currentProcess;
    q0.queue.push(p0);
    q0.queue.push(p1);

    while ((p0.ioQueue.size() != 0 || p1.ioQueue.size() != 0) && (!q0.queue.empty() || !q1.queue.empty())) {
        timeCounter++;
        poppedIOp0 =  false;
        poppedIOp1 = false;
        if (p0.remainingBurst == 0 && p0.ioQueue.size() != 0) {
            p0.ioQueue.front().timer++;
            if (p0.ioQueue.front().timer == IO_DURATION) {
                p0.ioQueue.pop();
                poppedIOp0 = true;
            }
        }
        if (p1.remainingBurst == 0 && p1.ioQueue.size() != 0) {
            p1.ioQueue.front().timer++;
            if (p1.ioQueue.front().timer == IO_DURATION) {
                p1.ioQueue.pop();
                poppedIOp1 = true;
            }
        } 
        if (!q0.queue.empty() && remainingQuantum != 0) {
            currentProcess = q0.queue.front();
            if (p0.id == currentProcess.id) {
                p0.remainingBurst--;
                remainingQuantum--;
                std::cout << "-p0-" << timeCounter;
                if (p0.remainingBurst == 0 || remainingQuantum == 0) {
                    q0.queue.pop();
                    remainingQuantum = q0.quantum;
                    if (p0.remainingBurst != 0) q1.queue.push(p0);
                }
            }
            else if (p1.id == currentProcess.id) {
                p1.remainingBurst--;
                remainingQuantum--;
                std::cout << "-p1-" << timeCounter;
                if (p1.remainingBurst == 0 || remainingQuantum == 0) {
                    q0.queue.pop();
                    remainingQuantum = q0.quantum;
                    if (p0.remainingBurst != 0) q1.queue.push(p1);
                }
            }
        }
        else if (!q1.queue.empty()) {
            currentProcess = q1.queue.front();
            if (p0.id == currentProcess.id) {
                p0.remainingBurst--;
                p1.waitingTime++;
                std::cout << "-p0-" << timeCounter;
                if (p0.remainingBurst == 0) q1.queue.pop();
                if (p1.waitingTime == MAX_WAITING_TIME) {
                    q1.queue.push(p1);
                    p1.waitingTime = 0;
                }
            }
            else if (p1.id == currentProcess.id) {
                p1.remainingBurst--;
                p0.waitingTime++;
                std::cout << "-p1-" << timeCounter;
                if (p1.remainingBurst == 0) q0.queue.pop();
                if (p0.waitingTime == MAX_WAITING_TIME) {
                    q1.queue.push(p0);
                    p0.waitingTime = 0;
                }
            }
        }
        if (poppedIOp0 == true && p0.ioQueue.size() != 0) {
            p0.remainingBurst = p0.burst;
            q0.queue.push(p0);
        }
        if (poppedIOp1 == true && p1.ioQueue.size() != 0) {
            p1.remainingBurst = p1.burst;
            q0.queue.push(p1);
        }
        std::cout<<" "<< timeCounter;
    }
    return 0;
}