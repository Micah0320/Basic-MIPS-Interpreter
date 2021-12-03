#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "globals.h"
void load_immediate()
{
    registers[operations[3]] = operations[2];
    if (operations[1])
        registers[operations[3]] = registers[operations[2]];
}

void add()
{
    registers[operations[3]] = registers[operations[2]] +
        registers[operations[1]];
}

void addi()
{
    registers[operations[3]] = operations[2] +
        registers[operations[1]];
}

void sub()
{
    registers[operations[3]] = registers[operations[1]] -
        registers[operations[2]];
}

void subi()
{
    registers[operations[3]] = registers[operations[1]] - operations[2];
}

void sll()
{
    registers[operations[3]] = (registers[operations[1]] << operations[2]);
}

void slr()
{
    registers[operations[3]] = (registers[operations[1]] >> operations[2]);
}

void andF()
{
    
    registers[operations[3]] = (registers[operations[1]] & registers[operations[2]]);

}

void orF()
{
    registers[operations[3]] = (registers[operations[1]] |  registers[operations[2]]);
}

void xorF()
{
    registers[operations[3]] = (registers[operations[1]] ^ registers[operations[2]]);
}
void nor()
{
    registers[operations[3]] = (~(registers[operations[1]] | registers[operations[2]]));

}

void slt()
{
    if (registers[operations[1]] < registers[operations[2]])
        registers[operations[3]] = registers[operations[1]];
    else
        registers[operations[3]] = registers[operations[2]];   

}

void mflo()
{
    registers[operations[3]] = LO;
}

void mfhi()
{
    registers[operations[3]] = HI;
}

void mult()
{
    LO = registers[operations[1]] * registers[operations[2]];
     
}

void div()
{
    if(registers[operations[2]] != 0)
    {
        LO = registers[operations[1]] / registers[operations[2]];
        HI = registers[operations[1]] % registers[operations[2]];
    }
}

void la()
{
    registers[operations[3]] = operations[2];
}

void lw()
{
    if (operations[2] % 4 == 0)
        
        registers[operations[3]] = Data[registers[operations[1]] + (operations[2] / 4)];
}

void sw()
{
    Data[registers[operations[1]] + (operations[2] / 4)] = registers[operations[3]];
}
//Syscall Functions
void printInt()
{
    std::cout << registers[4] << std::endl;
}

void readInt()
{
    std::cin >> registers[2];
}

void printChar()
{
    std::cout << char(registers[4]);
}

void printString()
{
    int i = registers[4];
    while(Data[i] != 0)
    {
        std::cout << char(Data[i]);
        ++i;
    }
    std::cout << std::endl;
}

void printProgram()
{
    for (int i = 0; i < Program.size(); ++i)
    {
        std::cout << *Program[i] << std::endl;
    }
}

void syscall()
{
    switch (operations[5])
    {
        case 0:
            printInt();
            break;
        case 4:
            printString();
            break;
        case 5:
            readInt();
            break;
        case 10:
            exitCase = 1;
            break;
        case 11:
            printChar();
            break;
    }
}

#endif
