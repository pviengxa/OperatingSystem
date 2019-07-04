//
// Created by User on 2019-03-13.
//

#include "SHORT_TERM_SCHEDULER.h"


namespace Project_Phase_One{

    void SHORT_TERM_SCHEDULER::schedule(std::list<Project_Phase_One::PCB> *PCB_in_RAM,
                                        std::list<Project_Phase_One::PCB> *ready_queue) {
        if(scheduler == FIFO){

            while(!PCB_in_RAM->empty()){
                std::list<Project_Phase_One::PCB>::iterator it = PCB_in_RAM->begin();
                ready_queue->push_back(*it);
                PCB_in_RAM->pop_front();

            }

        }
        else if (scheduler == PRIORITY){

            while(!PCB_in_RAM->empty()){
                std::list<Project_Phase_One::PCB>::iterator it = PCB_in_RAM->begin();
                int highest_priority = 30;
                int save_highest_priority_index = 0;
                int currentIndex = 0;
                for(auto current = PCB_in_RAM->begin(); current != PCB_in_RAM->end(); current++){
                    if(highest_priority > current->getPriority()){
                        currentIndex++;
                        save_highest_priority_index = currentIndex - 1;
                        highest_priority = current->getPriority();
                    }else
                        currentIndex++;

                }
                std::advance(it, save_highest_priority_index);
                it->setProcessStatus(READY);
                ready_queue->push_back(*it);
                PCB_in_RAM->erase(it);
                resetIterator(&it, save_highest_priority_index);
            }

        }
        else{
            while(!PCB_in_RAM->empty()){
                std::list<Project_Phase_One::PCB>::iterator it = PCB_in_RAM->begin();
                int shortest_job = 100000;
                int save_shortest_job_index = 0;
                int currentIndex = 0;
                for(auto current = PCB_in_RAM->begin(); current != PCB_in_RAM->end(); current++){
                    if(shortest_job > current->getNumberOfInstructions()){

                        currentIndex++;
                        save_shortest_job_index = currentIndex - 1;
                        shortest_job = current->getNumberOfInstructions();
                    }else
                        currentIndex++;

                }
                std::advance(it, save_shortest_job_index);
                it->setProcessStatus(READY);

                ready_queue->push_back(*it);
                PCB_in_RAM->erase(it);
                resetIterator(&it, save_shortest_job_index);
            }

        }

    }

    void SHORT_TERM_SCHEDULER::setScheduler(int schedulerIndex) {
        switch(schedulerIndex){
            case 0:
                scheduler = FIFO;
                break;
            case 1:
                scheduler = PRIORITY;
                break;
            case 2:
                scheduler = SBTF;
                break;
            default:
                std::cout<<"This scheduler does not exist."<<std::endl;

        }
    }

    void SHORT_TERM_SCHEDULER::resetIterator(std::list<Project_Phase_One::PCB>::iterator *it, const int index) {
        for(int i = index; i > 0; i--)
            it--;
    }
}