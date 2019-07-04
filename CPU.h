//
// Created by User on 2019-03-08.
//

#ifndef C_PROJECT_CPU_H
#define C_PROJECT_CPU_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include "LOADER.h"
#include "PCB.h"


namespace Project_Phase_One {
    enum ProcessorState{IDLE, UNLOADING, LOADING, EXECUTING};
    class CPU {
    private:
        int testing = 0;
        // The Jobs.
        int jobNumber, numberOfInstructions, dataAddress;

        // There's 16 registers.
        std::array<int, 16> registers;

        // These will be the registers for execution.
        int s_reg1, s_reg2, arithmetic_d_reg, branch_immediate_d_reg, b_reg, reg1, reg2, instuctionAddress;

        // The buffers.
        int inputBuffer, outputBuffer, tempBuffer;

        // The cache.
        int cacheSize;
        std::array<std::string, 72> cache;
        // The time spent one the CPU.
        int startTime, endTime, totalTime = 0;

        // The Instructions.
        int opCode;
        int programCounter;
        int IOCount;
        ProcessorState processorState;
        int cpuID;
        Project_Phase_One::Process_States processState;
        int jobRamIndex;

    public:
        //MARK: Constructor
        CPU();
        CPU(int cpuID);

        //MARK: Member Methods
        void executeInstructions();
        void runProcess(MEMORY_MANAGEMENT_UNIT *mmu);
        std::string fetchInstruction(int programCounter);
        void decode(std::string instruction);
        void setRegisters(std::string opCode);
        std::string hexToBinary(std::string hex);std::string decToHex(int dec);
        std::mutex PCB_lock;


        //MARK: Setter
        void setJobNumber(const int jobNumber){ this->jobNumber = jobNumber; }
        void setNumberOfInstructions(const int numberOfInstructions){ this->numberOfInstructions = numberOfInstructions; }
        void setInputBuffer(const int inputBuffer){ this->inputBuffer = inputBuffer; }
        void setOutputBuffer(const int outputBuffer){ this->outputBuffer = outputBuffer; }
        void setTempBuffer(const int tempBuffer){ this->tempBuffer = tempBuffer; }

        void setRegister(const std::array<int, 16> registers){this->registers = registers; }
        void setProcessorState( ProcessorState processorState){ this->processorState = processorState; }

        void setStartTime(const int startTime){ this->startTime = startTime; }
        void setEndTime(const int endTime){ this->endTime = endTime;}
        void setTotalTime(const int totalTime){ this->totalTime = totalTime;}

        void setProgramCounter(const int programCounter){ this->programCounter = programCounter; }
        void setProcessState(const Project_Phase_One::Process_States processState){ this->processState = processState; }
        void setCPUID(const int cpuID){ this->cpuID = cpuID; }
        void setIOCount(const int ioCount){ this->IOCount = IOCount; }
        void setCacheSize(const int cacheSize){ this->cacheSize = cacheSize;}
        void setCache(std::array<std::string, 72> cache){ this->cache = cache; }
        void setJobRamIndex(int jobRamIndex){ this->jobRamIndex = jobRamIndex; }


        //MARK: Getter
        int getJobNumber(){ return jobNumber; }
        int getNumberOfInstructions(){ return numberOfInstructions; }
        int getInputBuffer(){ return inputBuffer; }
        int getOutputBuffer(){ return outputBuffer; }
        int getTempBuffer(){ return tempBuffer; }
        std::array<int, 16> getRegister(){ return registers; }
        ProcessorState getProcessorState(){ return processorState; }
        int getStartTime(){ return startTime; }
        int getEndTime(){ return endTime; }
        int getTotalTime(){return totalTime; }
        int getProgramCounter(){ return programCounter; }
        Project_Phase_One::Process_States getProcessState(){ return processState; }
        int getCPUID(){ return cpuID; }
        int getIOCount(){ return IOCount; }
        int getCacheSize(){ return cacheSize; }
        std::array<std::string, 72> getCache(){ return cache;}
        int getJobRamIndex(){return jobRamIndex;}


    };

}

#endif //C_PROJECT_CPU_H
