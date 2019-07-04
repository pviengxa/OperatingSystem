//
// Created by User on 2019-03-10.
//

#include "LOADER.h"
#include "PCB.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


namespace Project_Phase_One{

    void LOADER::loading(std::string path, MEMORY_MANAGEMENT_UNIT *mmu, std::list<PCB> *newPCBList) {
        std::ifstream fileReader(path);
        std::string content;
        std::string findJob = "JOB";
        std::string findData = "Data";
        std::string findEND = "END";
        std::string findEmptyFrame = "EMPTY";
        int jobNumber = 0;
        int numberOfInstructions = 0;
        int priority = 0;
        int jobIndex = 0;

        if(!fileReader){

            std::cerr<<"Unable to open file: "<<path<<std::endl;
            exit(1);

        }

        while(std::getline(fileReader, content)){


            if(content.find(findJob) != std::string::npos){
                std::vector<std::string> jobToken;
                std::stringstream lookThrough(content);
                std::string intermediate;

                while(std::getline(lookThrough, intermediate, ' ')){
                    jobToken.push_back(intermediate);
                }

                JOB.setJobDiskIndex(index);
                jobNumber = std::stoi(jobToken[2], nullptr, 16);
                numberOfInstructions = std::stoi(jobToken[3], nullptr, 16);
                //priority = std::stoi(jobToken[2], nullptr, 16);
                priority = atoi(jobToken[4].c_str());
                jobIndex = index;

            }else if (content.find(findData) != std::string::npos){
                std::vector<std::string> dataToken;
                std::stringstream lookThrough(content);
                std::string intermediate;

                while(std::getline(lookThrough, intermediate,' ')){
                    dataToken.push_back(intermediate);
                }
                JOB = PCB(jobNumber, priority, numberOfInstructions, jobIndex);


                int inputBuffer = std::stoi(dataToken[2], nullptr, 16);
                int outputBuffer = std::stoi(dataToken[3], nullptr, 16);
                int tempBuffer = std::stoi(dataToken[4], nullptr, 16);


                JOB.setDataDiskIndex(index);
                JOB.setInputBuffer(inputBuffer);
                JOB.setOutputBuffer(outputBuffer);
                JOB.setTempBuffer(tempBuffer);


                newPCBList->push_back(JOB);

            }else if (content.find(findEND) != std::string::npos){
                // Don't do anything and continue.
                continue;

            }else {

                if(mmu->readFromDisk(index).find(findEmptyFrame) != std::string::npos){

                    mmu->writeToDisk(index, content);
                    index++;

                }else{
                    std::cout<<"this frame is not empty_frame."<<std::endl;

                }


            }


        }
        fileReader.close();

    }





}