//
// Created by User on 2019-04-23.
//

#include "PAGE_TABLE.h"


namespace Project_Phase_One{
    PAGE_TABLE::PAGE_TABLE() {
        number_of_Frame = MAX_FRAME_SIZE/4;
        for(int i = 0; i<number_of_Frame; i++){

            data[i] = 0;
            empty_frame[i] = false;
            offset_counter[i] = 0;

        }

    }
    PAGE_TABLE::PAGE_TABLE(int psize, int page_base_table) {

        this->page_size = psize;
        this->page_base_table = page_base_table;
        number_of_Frame = MAX_FRAME_SIZE/this->page_size;
        for(int i = 0; i<number_of_Frame; i++){

            data[i] = 0;
            empty_frame[i] = false;
            offset_counter[i] = 0;

        }

    }
    PAGE_TABLE::PAGE_TABLE(int psize, int page_base_table, int pID) {

        this->page_size = psize;
        this->page_base_table = page_base_table;
        this->pID = pID;

        number_of_Frame = MAX_FRAME_SIZE/this->page_size;
        for(int i = 0; i<number_of_Frame; i++){

            data[i] = 0;
            empty_frame[i] = false;
            offset_counter[i] = 0;

        }

    }
    void PAGE_TABLE::set_Frame(int frame_number, int page_number) {
        data[frame_number] = page_number;
        empty_frame[frame_number] = true;
        offset_counter[frame_number] = 0;

    }
    int PAGE_TABLE::find_free_frame(int instructionAddress) {
        int frame_numer = instructionAddress/16;
        if(empty_frame[frame_numer]){
            offset_counter[frame_numer]++;
            return (16*data[frame_numer]) + (instructionAddress - 16*frame_numer);

        }else{
            for(int i = 0; i<frame_numer; i++){
                offset_counter[i]--;

            }
            return -1;
        }


    }
    int PAGE_TABLE::least_use_frame() {
        int frame_number = 0;

        for (int i =0; i< frame_number; i++){
            if(empty_frame[i] && offset_counter[i] < offset_counter[frame_number]){
                frame_number = i;

            }

        }
        return 16*frame_number;

    }




}