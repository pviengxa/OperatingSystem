//
// Created by User on 2019-03-11.
//

#ifndef C_PROJECT_LONG_TERM_SCHEDULER_H
#define C_PROJECT_LONG_TERM_SCHEDULER_H
#include <iostream>
#include "LOADER.h"
#include "MEMORY_MANAGEMENT_UNIT.h"


namespace Project_Phase_One {

    class LONG_TERM_SCHEDULER {
    private:
        int const MAX_RAM_SPACE = 1024;
        int const MAX_DISK_SPACE = 2048;
        std::string const FIND_EMPTY_FRAME = "EMPTY";
        int index = 0;
    public:
        bool canAdd(std::list<PCB> *PCBInDISK) const;
        void LongTermSheduler(MEMORY_MANAGEMENT_UNIT *mmu, std::list<PCB> *PCBInDISK, std::list<PCB> *PCBInRAM);

    };

}
#endif //C_PROJECT_LONG_TERM_SCHEDULER_H