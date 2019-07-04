//
// Created by User on 2019-03-13.
//

#include "DRIVER.h"

namespace Project_Phase_One {
    DRIVER::DRIVER() {

    }

    void DRIVER::setFrameWork() {
        load.loading("/Users/testuser/Documents/Spring 2019/Operating System/Project_1 2/Program-File-Wordversion.txt", &mmu, &PCBInDISK);

        while(!PCBInDISK.empty()){

            longTerm.LongTermSheduler(&mmu, &PCBInDISK, &PCBInRAM);
            std::list<Project_Phase_One::PCB>::iterator it = PCBInRAM.begin();
            //std::cout<<"inst: "<<it->getNumberOfInstructions()<<" input: "<<it->getInputBuffer()<<" output"<<it->getOutputBuffer()<<" temp: "<<it->getTempBuffer()<<std::endl;

            //0:fifo, 1: Pri, 2: SJF
            shortTerm.setScheduler(1);


            shortTerm.schedule(&PCBInRAM, &ready_queue);
            initialTime = clock();
            while(!ready_queue.empty()){

                try {
                    if(ready_queue.size() > number_of_cpu_core){

                        std::vector<std::thread> threads;
                        //threads.reserve(number_of_cpu_core);
                        for(int i =0; i<number_of_cpu_core; i++){
                            threads.emplace_back(&Project_Phase_One::DRIVER::RUN, this);

                        }
                        for (auto &thread : threads) {
                            //std::cout<<"Thread ID is: "<<thread.get_id()<<"."<<std::endl;
                            thread.join();
                            //std::cout<<"Thread_ID executes at "<<clock()/double(CLOCKS_PER_SEC)<<"."<<std::endl;
                        }

                    }else{
                        //std::cout<<"this is the else statement and the size of the ready is "<<ready_queue.size()<<std::endl;
                        std::vector<std::thread> threads;
                        //threads.reserve(ready_queue.size());
                        for(int i =0; i<ready_queue.size(); i++){
                            threads.emplace_back(&Project_Phase_One::DRIVER::RUN, this);
                        }
                        for (auto &thread : threads) {
                            //std::cout<<"Thread ID is: "<<thread.get_id()<<"."<<std::endl;
                            thread.join();

                        }

                    }


                }catch (std::exception& exception ){

                    //std::cout<<"hellow world.\n";
                }

            }
            dumpRAM(&completed_jobs, &mmu);
        }





    }

    void DRIVER::dumpRAM(std::list<Project_Phase_One::PCB> *completed_jobs, MEMORY_MANAGEMENT_UNIT *mmu) {

        std::ofstream myfile;
        myfile.open("RAM DUMP");
        int total_time = 0;
        for(auto it = completed_jobs->begin(); it != completed_jobs->end(); it++){

            std::array<std::string, 72> RAMTemp = it->getCache();

            /*for (int i = 0; i < it->getCacheSize(); ++i) {
                if(i == 0){
                    myfile<<"JOB # "<<it->getJobNumber()<<"\n";
                    std::cout<<"\nJOB # "<<it->getJobNumber()<<std::endl;

                }
                else if (i == it->getNumberOfInstructions()){
                    myfile<<"INPUT_BUFFER\n";
                    std::cout<<"INPUT_BUFFER"<<std::endl;

                }
                else if(i == (it->getNumberOfInstructions() + it->getInputBuffer())){
                    myfile<<"OUTPUT_BUFFER\n";
                    std::cout<<"OUTPUT_BUFFER"<<std::endl;

                }
                else if(i == (it->getNumberOfInstructions() + it->getInputBuffer() + it->getOutputBuffer())){
                    myfile<<"TEMP_BUFFER\n";
                    std::cout<<"TEMP_BUFFER"<<std::endl;

                }
                myfile<<RAMTemp[i]<<"\n";
                std::cout<<RAMTemp[i]<<std::endl;

            }
*/
            total_time += it->getTimeSlice();
            std::cout<<"\nJob Number # "<<it->getJobNumber()<<" has completed execution."
                     <<"\nWait Time: "<<it->getTimeSlice()/double(CLOCKS_PER_SEC)<<" ns."
                     <<"\nTotal Wait time "<<total_time/double(CLOCKS_PER_SEC)
                     <<"\nBurst Time: "<<it->getBurstTIme()/double(CLOCKS_PER_SEC)<<" ns. "
                     <<"\ncache use: "<<(it->getCacheSize()/72.0)*100<<"%. "
                     <<"\nI/O Count: "<<it->getIOCount()
                     <<"\nNumber of Page used: "<<it->getCacheSize()/4.0<<std::endl;
            completed_jobs->pop_front();
        }



        if(ready_queue.empty()){
            for (int i = 0; i < 1024; i++){
                mmu->writeToRam(i , "EMPTY");
            }

        }

        myfile.close();
    }

    void DRIVER::RUN() {
        PCB_Lock.lock();
        switcher.loadPCBToCPU(&ready_queue, &cpu1);
        cpu1.runProcess(&mmu);
        switcher.unloadPCBFromCPU(&wait_queue, &completed_jobs, &cpu1, new PCB(), initialTime);
        PCB_Lock.unlock();

    }


}
