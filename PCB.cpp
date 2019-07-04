//
// Created by User on 2019-03-08.
//

#include "PCB.h"
#include <iostream>

namespace Project_Phase_One {
    // CONSTRUCTOR
    PCB::PCB(int jobNumber, int priority, int numberOfInstrucions, int jobDiskLocation) {
        this->jobNumber = jobNumber;
        this->priority = priority;
        this->numberOfInstructions = numberOfInstrucions;
        this->jobDiskIndex = jobDiskLocation;
        processStatus = NEW;
        registers[1] = 0;
        programCounter = 0;
        //IOCount = 0;

    }
    PCB::PCB(){
        processStatus = NEW;
        registers[1] = 0;
        programCounter = 0;
        //IOCount = 0;
    }

}