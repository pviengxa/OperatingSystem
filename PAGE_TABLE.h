//
// Created by User on 2019-04-23.
//

#ifndef PROJECT_1_PAGE_TABLE_H
#define PROJECT_1_PAGE_TABLE_H

#include <iostream>

namespace Project_Phase_One {
    class PAGE_TABLE {
    public:
        PAGE_TABLE();
        PAGE_TABLE(int psize, int page_base_table);
        PAGE_TABLE(int psize, int page_base_table, int pID);
        int find_free_frame(int instructionAddress);
        void set_Frame(int frame_number, int page_number);
        int least_use_frame();
    private:
        const static int MAX_FRAME_SIZE = 1024;
        const static int MAX_PAGE_SIZE = 2048;
        int pID;
        int number_of_Frame;
        bool is_Frame_full;
        int offset_count;
        int page_size;
        int page_base_table;
        int *data;
        bool *empty_frame;
        int *offset_counter;

    };
}

#endif //PROJECT_1_PAGE_TABLE_H
