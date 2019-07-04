//
// Created by User on 2019-04-21.
//

#ifndef C_PROJECT_MEMORY_MANAGEMENT_UNIT_H
#define C_PROJECT_MEMORY_MANAGEMENT_UNIT_H

#include <iostream>
#include <mutex>


namespace Project_Phase_One {

    class MEMORY_MANAGEMENT_UNIT {
    private:
        const static int MAX_DISK_SPACE = 2048;
        const static int MAX_RAM_SPACE = 1024;
        std::string DISK[MAX_DISK_SPACE];
        std::string RAM[MAX_RAM_SPACE];
        std::mutex lock;

    public:
        MEMORY_MANAGEMENT_UNIT();
        MEMORY_MANAGEMENT_UNIT(std::string *DISK, std::string *RAM);
        void writeToDisk(const int index, const std::string instruction);
        std::string readFromDisk(const int index);
        void writeToRam(const int index, const std::string instruction);
        std::string readFromRam(const int index);



    };

}

#endif //C_PROJECT_MEMORY_MANAGEMENT_UNIT_H