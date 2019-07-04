//
// Created by User on 2019-04-23.
//

#ifndef PROJECT_1_PAGE_SYSTEM_H
#define PROJECT_1_PAGE_SYSTEM_H

#include <iostream>
#include "MEMORY_MANAGEMENT_UNIT.h"
#include "PAGE_TABLE.h"


namespace Project_Phase_One {

    class PAGE_SYSTEM {
    private:
    public:
        void write(MEMORY_MANAGEMENT_UNIT *mmu, PAGE_TABLE *paging, const int index,const std::string entry);
        std::string read();
    };

}

#endif //PROJECT_1_PAGE_SYSTEM_H
