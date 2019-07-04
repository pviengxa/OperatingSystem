//
// Created by User on 2019-03-08.
//

#include "CPU.h"
#include <iostream>
#include <sstream>


//std::cout<<""<<std::endl;
namespace Project_Phase_One {
    //MARK: Constructor
    CPU::CPU(){
        processorState = IDLE;
        programCounter = 0;
    }
    CPU::CPU(int cpuID) {
        this->cpuID = cpuID;
        processorState = IDLE;
        programCounter = 0;


    }

    std::string CPU::fetchInstruction(int programCounter) {
        //std::lock_guard<std::mutex> G_lock(PCB_lock);
        return cache[programCounter];

    }

    void CPU::setRegisters(std::string instruction) {
        std::string instructionType = instruction.substr(0, 2);

        if (instructionType == "00") {
            //Arithmetic instruction format
            s_reg1 = std::stoi(instruction.substr(8, 4), nullptr, 2);
            s_reg2 = std::stoi(instruction.substr(12, 4), nullptr, 2);
            arithmetic_d_reg = std::stoi(instruction.substr(16, 4), nullptr, 2);

        } else if (instructionType == "01") {
            //Conditional Branch and Immediate format
            b_reg = std::stoi(instruction.substr(8, 4), nullptr, 2);
            branch_immediate_d_reg = std::stoi(instruction.substr(12, 4), nullptr, 2);
            instuctionAddress = std::stoi(instruction.substr(16), nullptr, 2);

        } else if (instructionType == "10") {
            //Unconditional Jump format
            instuctionAddress = std::stoi(instruction.substr(8), nullptr, 2);

        } else /*opCode == 11*/ {
            //Input and Output instruction format
            IOCount++;
            reg1 = std::stoi(instruction.substr(8, 4), nullptr, 2);
            reg2 = std::stoi(instruction.substr(12, 4), nullptr, 2);
            instuctionAddress = std::stoi(instruction.substr(16), nullptr, 2);

        }

    }

    void CPU::decode(std::string instruction) {
        //std::lock_guard<std::mutex> G_lcok(PCB_lock);
        std::string binary = hexToBinary(instruction);
        setRegisters(binary);
        opCode = std::stoi(binary.substr(2,6), nullptr, 2);

    }

    void CPU::executeInstructions() {
        //std::lock_guard<std::mutex> G_lock(PCB_lock);
        processorState = EXECUTING;
        std::stringstream stream;
        int temp = 0;


        switch(opCode) {
            case 0:// RD: Reads content of I/P into a accumulator.
                if (reg2 > 0) {

                    registers[reg1] = std::stoi(cache[(registers[reg2]) / 4].substr(2), nullptr, 16);


                } else {

                    registers[reg1] = std::stoi(cache[instuctionAddress / 4].substr(2), nullptr, 16);
                    //std::cout<<"else this is number "<<std::stoi(cache[instuctionAddress / 4].substr(2), nullptr, 16)<<std::endl;
                }

                programCounter++;

                break;
            case 1:// WR: Write the content of accumulator in to O/P buffer.

                if (reg2 > 0) {

                    registers[reg2] = registers[reg1];
                } else {

                    stream << "0x" << std::setfill('0') << std::setw(sizeof(int)*2)<< std::hex << registers[reg1];
                    /*std::cout << "Write " << stream.str() << " to cache[" << instuctionAddress / 4 << "]."
                              << std::endl;*/
                    cache[instuctionAddress / 4] = stream.str();
                }

                programCounter++;

                break;
            case 2://ST: Stores content of a reg. into a address.

                stream << "0x" << std::setfill('0') << std::setw(sizeof(int)*2)<< std::hex << registers[b_reg];

                cache[registers[branch_immediate_d_reg] / 4] = stream.str();

                programCounter++;

                break;
            case 3:// LW: Loads the content of an address into a reg.

                registers[branch_immediate_d_reg] = std::stoi((cache[((registers[b_reg] / 4) + instuctionAddress)].substr(2)), nullptr, 16);

                programCounter++;

                break;
            case 4:// MOV: Transfers the content of one register into another.

                registers[s_reg1] = registers[s_reg2];

                programCounter++;

                break;
            case 5:// ADD: Adds content of two S-regs into D-reg.

                temp = registers[s_reg1] + registers[s_reg2];
                registers[arithmetic_d_reg] = temp;

                programCounter++;

                break;
            case 6:// SUB: subtract content of two S-reg into D-reg.

                temp = registers[s_reg1] - registers[s_reg2];
                registers[arithmetic_d_reg] = temp;

                programCounter++;

                break;
            case 7:// MUL: Multiplies content of two s-reg into D-reg.

                temp = registers[s_reg1] * registers[s_reg2];
                registers[arithmetic_d_reg] = temp;


                programCounter++;

                break;
            case 8:// DIV: Divides content of two S-reg into D-reg;

                temp = registers[s_reg1] / registers[s_reg2];

                registers[arithmetic_d_reg] = temp;

                programCounter++;

                break;
            case 9:// AND: Logical AND of two S-reg into D-reg.

                registers[arithmetic_d_reg] = registers[s_reg1] && registers[s_reg2];

                programCounter++;

                break;
            case 10:// OR: Logical OR of two S-reg into D-reg.

                registers[arithmetic_d_reg] = registers[s_reg1] || registers[s_reg2];

                programCounter++;

                break;
            case 11:// MOVI: Transfers address/data directly into a register.

                registers[branch_immediate_d_reg] = instuctionAddress;

                programCounter++;

                break;
            case 12://ADDI: Adds a data value directly with the content of a register.

                registers[branch_immediate_d_reg] += instuctionAddress;

                programCounter++;

                break;
            case 13://MULI: Multiplies a data value directly with the content of a register.

                registers[branch_immediate_d_reg] *= instuctionAddress;

                programCounter++;

                break;
            case 14://DIVI: Divides a data directly with the content of a register.

                registers[branch_immediate_d_reg] /= instuctionAddress;

                programCounter++;

                break;
            case 15://LDI: Loads a data/address directly to the content of a register.

                registers[branch_immediate_d_reg] = instuctionAddress;

                programCounter++;

                break;
            case 16://SLT: Set the D-reg to 1 if first S-reg is less then the B-reg; 0 otherwise.
                if (registers[s_reg2] > registers[s_reg1]) {

                    registers[arithmetic_d_reg] = 1;

                } else {

                    registers[arithmetic_d_reg] = 0;
                }

                programCounter++;

                break;
            case 17://SLTI: Set the D-reg to 1 if first S-reg is less then a data; 0 otherwise.
                if ((instuctionAddress / 4) > registers[s_reg1]) {

                    registers[branch_immediate_d_reg] = 1;
                } else {

                    registers[branch_immediate_d_reg] = 0;
                }

                programCounter++;

                break;
            case 18://HLT: Logical end of program.
                programCounter = numberOfInstructions;


                break;
            case 19://NOP: Does nothing and moves to the next instruction.


                break;
            case 20://JMP: Jumps to a specified location.

                programCounter = instuctionAddress;// / 4;

                break;
            case 21://BEQ: Branches to an address when content of B-reg = D-reg.

                if (registers[b_reg] == registers[branch_immediate_d_reg]) {

                    programCounter = instuctionAddress / 4;
                }else{

                    programCounter++;

                }
                break;
            case 22://BNE: Branches to an address when content of B-reg <> D-reg.std::cout<<"executing "<<opCode<<std::endl;
                //std::cout<<"this is opcode 22"<<std::endl;
                if (registers[b_reg] != registers[branch_immediate_d_reg]) {

                    programCounter = instuctionAddress / 4;

                }else{

                    programCounter++;

                }
                break;
            case 23://BEZ: Branches to an address when content of B-reg = 0.

                if (registers[b_reg] == 0) {

                    programCounter = instuctionAddress / 4;
                }else{
                    programCounter++;

                }
                break;
            case 24://BNZ: Branches to an address when content of B-reg <> 0.
                if(registers[b_reg] != 0) {

                    programCounter = instuctionAddress / 4;
                }else{

                    programCounter++;

                }
                break;
            case 25://BGZ: Branches to an address when content of B-reg > 0.
                if(registers[b_reg] > 0) {

                    programCounter = instuctionAddress / 4;
                }else{

                    programCounter++;

                }
                break;
            case 26://BLZ: Branches to an address when content of B-reg < 0.
                if(registers[b_reg] < 0) {

                    programCounter = instuctionAddress / 4;

                }else {

                    programCounter++;

                }
                break;
            default:std::cout<<"INVALID OPCODE."<<std::endl;


        }




    }


    void CPU::runProcess(MEMORY_MANAGEMENT_UNIT *mmu) {
        // Set the cache
        cacheSize = numberOfInstructions + inputBuffer + outputBuffer + tempBuffer;
        for(int i = 0; i < cacheSize; i++){
            cache[i] = mmu->readFromRam(jobRamIndex++);

        }
        // Set I/O counter to zero.
        IOCount = 0;


        while(numberOfInstructions > programCounter){
            std::lock_guard<std::mutex> G_lock(PCB_lock);
            std::string executable_instructions = fetchInstruction(programCounter);

            decode(executable_instructions);

            executeInstructions();



        }


    }



    std::string CPU::hexToBinary(std::string hex) {
        //std::lock_guard<std::mutex> G_lock(PCB_lock);
        std::string binary = "";

        for (int i = 2; i < (hex.length()-1); i++) {

            switch (hex[i]) {
                case '0':
                    binary += "0000";
                    break;
                case '1':
                    binary += "0001";
                    break;
                case '2':
                    binary += "0010";
                    break;
                case '3':
                    binary += "0011";
                    break;
                case '4':
                    binary += "0100";
                    break;
                case '5':
                    binary += "0101";
                    break;
                case '6':
                    binary += "0110";
                    break;
                case '7':
                    binary += "0111";
                    break;
                case '8':
                    binary += "1000";
                    break;
                case '9':
                    binary += "1001";
                    break;
                case 'A':
                    binary += "1010";
                    break;
                case 'B':
                    binary += "1011";
                    break;
                case 'C':
                    binary += "1100";
                    break;
                case 'D':
                    binary += "1101";
                    break;
                case 'E':
                    binary += "1110";
                    break;
                case 'F':
                    binary += "1111";
                    break;
                case ' ':
                    break;
                default:
                    std::cout << "invalid hex character. "<<hex[i]<< std::endl;


            }

        }

        return binary;

    }





}
