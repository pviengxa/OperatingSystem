//
// Created by User on 2019-03-11.
//

#include "LONG_TERM_SCHEDULER.h"

namespace Project_Phase_One {


    void LONG_TERM_SCHEDULER::LongTermSheduler(MEMORY_MANAGEMENT_UNIT *mmu,
                                               std::list<Project_Phase_One::PCB> *PCBInDISK,
                                               std::list<Project_Phase_One::PCB> *PCBInRAM) {
        index = 0;
        while(!PCBInDISK->empty() && canAdd(PCBInDISK)){
            std::list<Project_Phase_One::PCB>::iterator it = PCBInDISK->begin();
            int disk_index = it->getJobDiskIndex();
            int size_of_instructions = it->getNumberOfInstructions()+
                                       it->getInputBuffer()+
                                       it->getOutputBuffer()+
                                       it->getTempBuffer();
            if(MAX_RAM_SPACE > (size_of_instructions + index)){
                it->setIsPCBInRam(true);
                it->setJobRamIndex(index);
                PCBInRAM->push_back(*it);
                for(int i = 0; i < size_of_instructions; i++){
                    if (mmu->readFromRam(index).find(FIND_EMPTY_FRAME) != std::string::npos){

                        //RAM[index++] = DISK[disk_index++];
                        mmu->writeToRam(index++, mmu->readFromDisk(disk_index++));

                    }else {

                        std::cout<<"This frame is not empty_frame"<<std::endl;

                    }
                }
                PCBInDISK->pop_front();
            }

        }


    }

    bool LONG_TERM_SCHEDULER::canAdd(std::list<PCB> *PCBInDISK) const {
        std::list<Project_Phase_One::PCB>::iterator it = PCBInDISK->begin();
        int size_of_instruction = it->getNumberOfInstructions()+
                                  it->getOutputBuffer()+
                                  it->getInputBuffer()+
                                  it->getTempBuffer();
        return MAX_RAM_SPACE > (index + size_of_instruction);

    }


}
