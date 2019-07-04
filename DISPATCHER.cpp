//
// Created by User on 2019-04-16.
//

#include "DISPATCHER.h"

namespace Project_Phase_One{
    void DISPATCHER::loadPCBToCPU(std::list<Project_Phase_One::PCB> *ready_queue, CPU *cpu) {
        std::lock_guard<std::mutex> G_lock(PCB_Lock);
        cpu->setStartTime(clock());

        std::list<Project_Phase_One::PCB>::iterator it = ready_queue->begin();

        cpu->setProcessorState(LOADING);



        cpu->setJobRamIndex(it->getJobRamIndex());
        cpu->setJobNumber(it->getJobNumber());
        cpu->setProgramCounter(it->getProgramCounter());
        cpu->setProcessState(READY);
        cpu->setInputBuffer(it->getInputBuffer());
        cpu->setOutputBuffer(it->getOutputBuffer());
        cpu->setTempBuffer(it->getTempBuffer());
        cpu->setRegister(it->getRegisters());
        cpu->setNumberOfInstructions(it->getNumberOfInstructions());
        cpu->setCPUID(it->get_CPU_ID());
        cpu->setIOCount(0);

        cpu->setCacheSize(cpu->getInputBuffer() + cpu->getOutputBuffer() + cpu->getTempBuffer() + cpu->getNumberOfInstructions());


        ready_queue->pop_front();

    }

    void DISPATCHER::unloadPCBFromCPU(std::list<Project_Phase_One::PCB> *wait_queue,
                                      std::list<Project_Phase_One::PCB> *completed_job,
                                      CPU *cpu, Project_Phase_One::PCB *pcb,
                                      int initial_time) {
        //std::lock_guard<std::mutex> G_lock(PCB_Lock);
        cpu->setEndTime(clock());

        cpu->setProcessorState(UNLOADING);

        pcb->set_CPU_ID(cpu->getCPUID());
        pcb->setJobNumber(cpu->getJobNumber());
        pcb->setBurstTIme(cpu->getEndTime() - cpu->getStartTime());
        pcb->setNumberOfInstructions(cpu->getNumberOfInstructions());
        pcb->setRegisters(cpu->getRegister());
        pcb->setOutputBuffer(cpu->getOutputBuffer());
        pcb->setInputBuffer(cpu->getInputBuffer());
        pcb->setTempBuffer(cpu->getTempBuffer());
        pcb->setProgramCounter(cpu->getProgramCounter());
        pcb->setCacheSize(cpu->getCacheSize());
        pcb->setCache(cpu->getCache());
        pcb->setIOCount(cpu->getIOCount());
        pcb->setTimeSlice(cpu->getEndTime() - initial_time);


        if(cpu->getNumberOfInstructions() > cpu->getProgramCounter()){
            pcb->setProcessStatus(WAITING);
            wait_queue->push_back(*pcb);
        }
        else {

            pcb->setProcessStatus(TERMINATE);
            //std::cout<<"\n* Job # "<<cpu->getJobNumber()<<"*"<<std::endl;
            //std::cout<<"* There was "<<cpu->getIOCount()<<" I/O counts.*"<<std::endl;
            //std::cout<<"* This process spend "<<(cpu->getEndTime()-cpu->getStartTime())/double(CLOCKS_PER_SEC)<<" seconds on the CPU.*"<<std::endl;
            //cpu->setTotalTime(cpu->getEndTime() - cpu->getStartTime());
            //pcb->setBurstTIme((cpu->getEndTime()-cpu->getStartTime())/double(CLOCKS_PER_SEC));
            //totalTime += (cpu->getEndTime() - cpu->getStartTime());
            //std::cout<<"* The total process time "<<totalTime/double(CLOCKS_PER_SEC)<<"*"<<std::endl;
            //pcb->setIOCount(cpu->getIOCount());
            pcb->setBurstTIme((cpu->getEndTime()-cpu->getStartTime()));
            completed_job->push_back(*pcb);


        }


    }

}