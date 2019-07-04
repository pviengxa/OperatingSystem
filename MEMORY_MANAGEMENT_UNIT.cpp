//
// Created by User on 2019-04-21.
//

#include "MEMORY_MANAGEMENT_UNIT.h"


namespace Project_Phase_One{
    MEMORY_MANAGEMENT_UNIT::MEMORY_MANAGEMENT_UNIT() {

        for (int i = 0; i < MAX_DISK_SPACE; i++){
            DISK[i] = "EMPTY";
        }

        for (int i = 0; i < MAX_RAM_SPACE; i++){
            RAM[i] = "EMPTY";
        }


    }

    void MEMORY_MANAGEMENT_UNIT::writeToDisk(const int index, const std::string instruction) {
        lock.lock();
        DISK[index] = instruction;
        lock.unlock();
    }

    std::string MEMORY_MANAGEMENT_UNIT::readFromDisk(const int index) {
        std::lock_guard<std::mutex> G_lock(lock);
        return DISK[index];
    }

    void MEMORY_MANAGEMENT_UNIT::writeToRam(const int index, const std::string instruction) {
        lock.lock();
        RAM[index] = instruction;
        lock.unlock();
    }

    std::string MEMORY_MANAGEMENT_UNIT::readFromRam(const int index) {
        std::lock_guard<std::mutex> G_lock(lock);
        return RAM[index];
    }




}