#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <list>
#include <ctime>
#include <chrono>
#include <mutex>
#include <array>
#include "PCB.h"
#include "CPU.h"
#include "LOADER.h"
#include "LONG_TERM_SCHEDULER.h"
#include "SHORT_TERM_SCHEDULER.h"
#include "DRIVER.h"


int main() {
    int start = clock();
    Project_Phase_One::DRIVER driver;
    std::cout<<"Operating System START: "<<start/double(CLOCKS_PER_SEC)<<std::endl;
    driver.setFrameWork();
    int end = clock();
    std::cout<<"\nOperating System END: "<<end/double(CLOCKS_PER_SEC)<<std::endl;
    std::cout<<"Operating System TOTAL: "<<(end-start)/double(CLOCKS_PER_SEC)<<std::endl;



    return 0;
}