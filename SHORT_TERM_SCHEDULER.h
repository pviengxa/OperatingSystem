//
// Created by User on 2019-03-13.
//

#ifndef C_PROJECT_SHORT_TERM_SCHEDULER_H
#define C_PROJECT_SHORT_TERM_SCHEDULER_H

#include <iostream>
#include <list>
#include "LONG_TERM_SCHEDULER.h"
#include "PCB.h"


namespace Project_Phase_One {
    class SHORT_TERM_SCHEDULER {
    public:
        enum Scheduler_Type {FIFO, SBTF, PRIORITY};
    private:
        /*
         * FIFO = First in First Out
         * SBTF = Shortest Burst Time First
         * PRIORITY = Highest priority first, the lower the number the higher the priority.
         * */
        Scheduler_Type scheduler = FIFO;
    public:
        //The
        void schedule(std::list<Project_Phase_One::PCB> *PCB_in_RAM, std::list<Project_Phase_One::PCB> *ready_queue);

        // SETTER
        void setScheduler(int schedulerIndex);
        void resetIterator(std::list<Project_Phase_One::PCB>::iterator *it, const int index);


    };

}
#endif //C_PROJECT_SHORT_TERM_SCHEDULER_H