//
// Created by User on 2019-03-08.
//

#ifndef C_PROJECT_PCB_H
#define C_PROJECT_PCB_H

#include <iostream>
#include <array>


namespace Project_Phase_One {
    enum Process_States{NEW, READY, RUNNING, WAITING, TERMINATE};
    class PCB{
    private:
        int cpuID;
        int programCounter;
        int numberOfInstructions;
        int jobNumber;
        int cacheSize;
        int jobDiskIndex;
        int jobRamIndex;
        Process_States processStatus;
        int priority;
        std::array<int, 16> registers;
        int IOCount;

        // Data
        int dataDiskIndex;
        int dataRamIndex;
        int inputBuffer;
        int outputBuffer;
        int tempBuffer;

        // Schedule
        int burstTime, timeSlice, timeRemaining;

        // Account
        int cupTime, timeLimit, timeDelay, startTime, endTime, ioTime;

        // Memories
        int pageTableBase, pages, pageSize;

        // Progeny
        int childProcessID;
        PCB* childLeft_ptr;
        PCB* childRight_ptr;
        PCB* parent_ptr;

        // Resources
        bool isPCBInRam;
        int unitNumber;
        std::array<std::string, 72> cache;
    public:
        // CONSTRUCTOR
        PCB(int jobNumber, int priority, int numberOfInstrucions, int jobDiskLocation);
        PCB();
        // The Getter will return a private member of this class.
        int getIOCount(){ return IOCount; }
        int get_CPU_ID(){ return cpuID; }
        int getProgramCounter(){ return programCounter; }
        int getJobNumber(){ return jobNumber; }
        int getNumberOfInstructions(){ return numberOfInstructions; }
        int getJobDiskIndex(){ return jobDiskIndex; }
        int getJobRamIndex(){return jobRamIndex; }
        int getCacheSize(){ return cacheSize; }
        Process_States getProcessStatus(){ return processStatus; }
        int getPriority(){ return priority; }
        std::array<int, 16> getRegisters(){ return registers; }
        int getDataDiskIndex(){ return dataDiskIndex; }
        int getDataRamIndex(){ return dataRamIndex; }
        int getInputBuffer(){ return inputBuffer; }
        int getOutputBuffer(){ return outputBuffer; }
        int getTempBuffer(){ return tempBuffer; }
        int getBurstTIme(){ return burstTime; }
        int getTimeSlice(){ return timeSlice; }
        int getTimeRemaining(){ return timeRemaining; }
        int getPageTableBase(){ return pageTableBase; }
        int getPages(){ return pages; }
        int getPageSize(){ return pageSize; }
        int getChildProcessID(){ return childProcessID; }
        PCB* getChildLeft(){ return childLeft_ptr; }
        PCB* getChildRight(){ return childRight_ptr; }
        PCB* getParent(){ return parent_ptr; }
        std::array<std::string, 72> getCache(){ return cache; }
        bool getIsPCBInRam(){ return isPCBInRam; }

        // The Setter will set the member of this class

        void setIOCount(int IOCount){ this->IOCount = IOCount; }
        void set_CPU_ID(int cpuID){ this->cpuID = cpuID; }
        void setProgramCounter(int programCounter){ this->programCounter = programCounter; }
        void setJobNumber(int jobNumber){ this->jobNumber = jobNumber; }
        void setJobDiskIndex(int jobDiskIndex){ this->jobDiskIndex = jobDiskIndex; }
        void setJobRamIndex(int jobRamIndex){ this->jobRamIndex = jobRamIndex; }
        void setNumberOfInstructions(int numberOfInstructions){ this->numberOfInstructions = numberOfInstructions; }
        void setCacheSize(int cacheSize){ this->cacheSize = cacheSize; }
        void setProcessStatus(Process_States processStatus){ this->processStatus = processStatus; }
        void setPriority(int priority){ this->priority = priority; }
        void setRegisters(std::array<int, 16> registers){ this->registers = registers;}
        void setDataDiskIndex(int dataDiskIndex){ this->dataDiskIndex = dataDiskIndex; }
        void setDataRamIndex(int dataRamIndex){ this->dataRamIndex = dataRamIndex; }
        void setInputBuffer(int inputBuffer){ this->inputBuffer = inputBuffer; }
        void setOutputBuffer(int outputBuffer){ this->outputBuffer = outputBuffer; }
        void setTempBuffer(int tempBuffer){ this->tempBuffer = tempBuffer; }
        void setBurstTIme(int burstTime){this->burstTime = burstTime; }
        void setTimeSlice(int timeSlice){ this->timeSlice = timeSlice; }
        void setTimeRemaining(int timeRemaining){ this->timeRemaining = timeRemaining; }
        void setPageTableBase(int pageTableBase){ this->pageTableBase = pageTableBase; }
        void setPages(int pages){ this->pages = pages; }
        void setPageSize(int pageSize){ this->pageSize = pageSize; }
        void setChildProcessID(int childProcessID){ this->childProcessID = childProcessID; }
        void setChildCodePointerLeft(PCB* childLeft_ptr){ this->childLeft_ptr = childLeft_ptr; }
        void setChildCodePointerRight(PCB* childRight_ptr){ this->childRight_ptr = childRight_ptr; }
        void setParent(PCB* parent_ptr){ this->parent_ptr = parent_ptr; }
        void setCache(std::array<std::string, 72> cache){ this->cache = cache; }
        void setIsPCBInRam(const bool isPCBInRam){ this->isPCBInRam = isPCBInRam; }
    };

}



#endif //C_PROJECT_PCB_H