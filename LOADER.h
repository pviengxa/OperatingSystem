//
// Created by User on 2019-03-10.
//

#ifndef C_PROJECT_LOADER_H
#define C_PROJECT_LOADER_H

#include <iostream>
#include <list>
#include "PCB.h"
#include "MEMORY_MANAGEMENT_UNIT.h"
namespace Project_Phase_One{
    class LOADER {
    private:
        PCB JOB;
        int index = 0;


    public:
        void loading(std::string path, MEMORY_MANAGEMENT_UNIT *mmu, std::list<PCB> *newPCBList);


    };

}

#endif //C_PROJECT_LOADER_H