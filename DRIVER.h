//
// Created by User on 2019-03-13.
//

#ifndef C_PROJECT_DRIVER_H
#define C_PROJECT_DRIVER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include "PCB.h"
#include "LOADER.h"
#include "LONG_TERM_SCHEDULER.h"
#include "SHORT_TERM_SCHEDULER.h"
#include "CPU.h"
#include "DISPATCHER.h"
#include "MEMORY_MANAGEMENT_UNIT.h"

namespace Project_Phase_One{

    class DRIVER {
    private:
        // Mark: Software
        const static int number_of_cpu_core = 4;
        LOADER load;
        LONG_TERM_SCHEDULER longTerm;
        SHORT_TERM_SCHEDULER shortTerm;
        DISPATCHER switcher;
        MEMORY_MANAGEMENT_UNIT mmu;

        std::list<Project_Phase_One::PCB> PCBInDISK;
        std::list<Project_Phase_One::PCB> PCBInRAM;
        std::list<Project_Phase_One::PCB> ready_queue;
        std::list<Project_Phase_One::PCB> wait_queue;
        std::list<Project_Phase_One::PCB> completed_jobs;
        // Mark: Hardware
        std::string RAM[1024];
        std::string DISK[2048];
        std::mutex PCB_Lock;
        CPU cpu[4];
        CPU cpu1;
        int initialTime = 0;
    public:
        DRIVER();
        void setFrameWork();
        void dumpRAM(std::list<Project_Phase_One::PCB> *completed_jobs, MEMORY_MANAGEMENT_UNIT *mmu);
        void RUN();

    };

}

#endif //C_PROJECT_DRIVER_H