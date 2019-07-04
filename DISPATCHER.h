//
// Created by User on 2019-04-16.
//

#ifndef C_PROJECT_CONTENT_SWITCHER_H
#define C_PROJECT_CONTENT_SWITCHER_H
#include <iostream>
#include <list>
#include <chrono>
#include <ctime>
#include <mutex>
#include "PCB.h"
#include "CPU.h"

namespace Project_Phase_One{

    class DISPATCHER {
    public:
        void loadPCBToCPU(std::list<Project_Phase_One::PCB> *ready_queue, CPU *cpu);
        void unloadPCBFromCPU(std::list<Project_Phase_One::PCB> *wait_queue, std::list<Project_Phase_One::PCB> *completed_jobs,
                              CPU *cpu, Project_Phase_One::PCB *pcb, int initial_time);
    private:
        std::mutex PCB_Lock;

    };


}


#endif //C_PROJECT_CONTENT_SWITCHER_H
