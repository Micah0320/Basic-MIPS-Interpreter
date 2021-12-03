#ifndef UTIL_H
#define UTIL_H
#include <cstring>
#include "functions.h"

void printReg();
void printOps();
void MIPS();


//Clears registers and operations;
void init()
{
    for (int i; i < 32; ++i)
    {
        if (i < 6)
        {
            operations[i] = 0;
        }
        registers[i] = 0;
    }
}

//Returns the command that will be executed
void tokenizerCommand(char input[])
{
    if (prompt && !mode)
        return;
    if (outLabels.size() == 0 || !branched)
        execute = 1;
    std::string * inputString = new std::string;
    *(inputString) = input;
    if (!secondTime)
        Program.push_back(inputString);
    //booleans used for checking ops
    bool rs = 0;
    bool rt = 0;
    bool rd = 0;
    bool opIded = 0;
    bool labelIDed = 0;
    for (int i = 0; i < MAX_BUF; ++i)
    {

        if (rs && rt && rd)
            break;
        //printOps();
        //std::cout << i << ' ' << input[i] << std::endl;
        if (input[i] == ' ' || input[i] == '\t' || input[i] == ',')
            continue;

        //Tokenizes a Label (Similar to int tokenization)
        //At the begining of a function
        if (input[i] >= 65 && input[i] <= 90 && !opIded && !prompt)
        {
            std::string * labelString = new std::string;
            
            while (i < MAX_BUF)
            {
                if (input[i] == ':')
                    break;
                *(labelString) += input[i];
                ++i;
            }
            if (outLabels.size() > 0)
            {
                
                if (*(labelString) == outLabels[outLabels.size() - 1])
                {
                    outLabels.pop_back();
                    if (branched)
                        branched = 0;
                    
                }
            }
            
            //Makes sure the label isn't already used before pushing back label
            for(int j = 0; i < Labels.size(); +j)
            {
                if (*labelString == *Labels[j])
                {
                    goto endCheck;
                }
            }
            Labels.push_back(labelString);
            position.push_back(program_counter);
            labelIDed = 1;
            break;
        }
      endCheck:
        if (!opIded)
        {
            //Checks to see if user wants to see text/labels/registers/data
            if (input[i] == 's' && input[i + 1] == 'h' && input[i + 2] == 'o' &&
                input[i + 3] == 'w')
            {
                switch (input[i + 5])
                {
                    case 't':
                        Program.pop_back();
                        program_counter--;
                        operations[0] = -2;
                        operations[5] = 0;
                        break;
                    case 'l':
                        Program.pop_back();
                        program_counter--;
                        operations[0] = -2;
                        operations[5] = 1;
                        break;
                    case 'r':
                        Program.pop_back();
                        program_counter--;
                        operations[0] = -2;
                        operations[5] = 2;
                        break;
                    case 'd':
                        Program.pop_back();
                        program_counter--;
                        operations[0] = -2;
                        operations[5] = 3;
                        break;
                }
                break;
                
            }

            if (input[i] == 'd' && input[i + 1] == 'a' && input[i + 2] =='t' && input[i + 3] == 'a')
            {
                Program.pop_back();
                program_counter--;
                enterData = 1;
                break;
            }

            
            //j command
            if (input[i] == 'j' && (input[i + 1] ==' ' || input[i + 1] == '\t'))
            {
                    //Sets the operation Code to 2,
                    //Function Code to 0,
                    //and Shift amount to 0.
                    //Also sets rs to 0;
                    operations[0] = 2;
                    operations[5] = 0;
                    operations[4] = 0;
                    operations[1] = 0;
                    rs = 1;
                    rd = 1;
                    i += 1;
                    opIded = 1;
            }
            if (input[i] == 'b')
            {
                if (input[i + 1] == 'e' && input[i + 2] == 'q' && (
                        input[i + 3] == ' ' || input[i + 3] == '\t'))
                    {
                        operations[0] = 2;
                        operations[5] = 1;
                        operations[4] = 0;
                        i += 3;
                        opIded = 1;
                    }
                if (input[i + 1] == 'n' && input[i + 2] == 'e' && (
                        input[i + 3] == ' ' || input[i + 3] == '\t'))
                    {
                        operations[0] = 2;
                        operations[5] = 2;
                        operations[4] = 0;
                        i += 3;
                        opIded = 1;
                    }
                if (input[i + 1] == 'l' && input[i + 2] == 't' && (
                        input[i + 3] == ' ' || input[i + 3] == '\t'))
                    {
                        operations[0] = 2;
                        operations[5] = 3;
                        operations[4] = 0;
                        i += 3;
                        opIded = 1;
                    }
                if (input[i + 1] == 'g' && input[i + 2] == 't' && (
                        input[i + 3] == ' ' || input[i + 3] == '\t'))
                    {
                        operations[0] = 2;
                        operations[5] = 4;
                        operations[4] = 0;
                        i += 3;
                        opIded = 1;
                    }
                if (input[i + 1] == 'l' && input[i + 2] == 'e' && (
                        input[i + 3] == ' ' || input[i + 3] == '\t'))
                    {
                        operations[0] = 2;
                        operations[5] = 5;
                        operations[4] = 0;
                        i += 3;
                        opIded = 1;
                    }
                if (input[i + 1] == 'g' && input[i + 2] == 'e' && (
                        input[i + 3] == ' ' || input[i + 3] == '\t'))
                    {
                        operations[0] = 2;
                        operations[5] = 6;
                        operations[4] = 0;
                        i += 3;
                        opIded = 1;
                    }
            }
            //li command
            if (input[i] == 'l')
            {
                if (input[i + 1] == 'i' && (input[i + 2] == ' '
                                            || input[i + 2] == '\t'))
                {
                    //Sets the operation Code to 1,
                    //Function Code to 48,
                    //and Shift amount to 0.
                    //Also sets rs to 0;
                    operations[0] = 1;
                    operations[5] = 48;
                    operations[4] = 0;
                    operations[1] = 0;
                    rs = 1;
                    i += 2;
                    opIded = 1;
                }
            }
            //move command
            if (input[i] == 'm')
            {
                if (input[i + 1] == 'o' &&  input[i + 2] == 'v' && input[i + 3] == 'e' &&(input[i + 4] == ' '
                                            || input[i + 4] == '\t'))
                {
                    //Sets the operation Code to 1,
                    //Function Code to 48,
                    //and Shift amount to 0.
                    //Also sets rs to 1;
                    operations[0] = 1;
                    operations[5] = 48;
                    operations[4] = 0;
                    operations[1] = 1;
                    rs = 1;
                    i += 4;
                    opIded = 1;
                }
            }
            //mflo command
            if (input[i] == 'm')
            {
                if (input[i + 1] == 'f' &&  input[i + 2] == 'l' && input[i + 3] == 'o' &&(input[i + 4] == ' '
                                            || input[i + 4] == '\t'))
                {
                    //Sets the operation Code to 1,
                    //Function Code to 48,
                    //and Shift amount to 0.
                    //Also sets rs to 1 and rt to 1;
                    operations[0] = 0;
                    operations[5] = 18;
                    operations[4] = 0;
                    operations[1] = 0;
                    rs = 1;
                    rt = 1;
                    i += 4;
                    opIded = 1;
                }
            }
            //mfhi command
            if (input[i] == 'm')
            {
                if (input[i + 1] == 'f' &&  input[i + 2] == 'h' && input[i + 3] == 'i' &&(input[i + 4] == ' '
                                            || input[i + 4] == '\t'))
                {
                    //Sets the operation Code to 1,
                    //Function Code to 48,
                    //and Shift amount to 0.
                    //Also sets rs to 1 and rt to 1;
                    operations[0] = 0;
                    operations[5] = 19;
                    operations[4] = 0;
                    operations[1] = 0;
                    rs = 1;
                    rt = 1;
                    i += 4;
                    opIded = 1;
                }
            }
            //mult command
            if (input[i] == 'm')
            {
                if (input[i + 1] == 'u' &&  input[i + 2] == 'l' && input[i + 3] == 't' &&(input[i + 4] == ' '
                                            || input[i + 4] == '\t'))
                {
                    //Sets the operation Code to 1,
                    //Function Code to 48,
                    //and Shift amount to 0.
                    //Also sets rs to 1 and rt to 1;
                    operations[0] = 0;
                    operations[5] = 26;
                    operations[4] = 0;
                    operations[3] = 0;
                    rd = 1;
                    i += 4;
                    opIded = 1;
                }
            }
            //div command
            if (input[i] == 'd')
            {
                if (input[i + 1] == 'i' &&  input[i + 2] == 'v'  &&(input[i + 3] == ' '
                                            || input[i + 3] == '\t'))
                {
                    //Sets the operation Code to 1,
                    //Function Code to 48,
                    //and Shift amount to 0.
                    //Also sets rs to 1 and rt to 1;
                    operations[0] = 0;
                    operations[5] = 28;
                    operations[4] = 0;
                    operations[3] = 0;
                    rd = 1;
                    i += 3;
                    opIded = 1;
                }
            }
            //add and addi commands
            if (input[i] == 'a')
            {
                if (input[i + 1] == 'd' && input[i + 2] == 'd')
                {
                    if(input[i + 3] == ' '
                        || input[i + 3] == '\t')
                    {
                        //Sets the operation Code to 0,
                        //Function Code to 32,
                        //and Shift amount to 0.
                        operations[0] = 0;
                        operations[5] = 32;
                        operations[4] = 0;
                        input += 3;
                        opIded = 1;
                    }
                    if(input[i + 3] == 'i' && (input[i+4] == ' '
                                               || input[i + 4] == '\t'))
                    {
                        //addi
                        operations[0] = 1;
                        operations[5] = 32;
                        operations[4] = 0;
                        input += 4;
                        opIded = 1;
                    }
                }
            }
            //sll command
            if (input[i] == 's')
            {
                if (input[i + 1] == 'l' && input[i + 2] == 'l')
                {
                    if(input[i + 3] == ' '
                        || input[i + 3] == '\t')
                    {
                        //Sets the operation Code to 0,
                        //Function Code to 32,
                        //and Shift amount to 0.
                        operations[0] = 0;
                        operations[5] = 0;
                        operations[4] = 0;
                        input += 3;
                        opIded = 1;
                    }
                }
            }
            //slr command
            if (input[i] == 's')
            {
                if (input[i + 1] == 'l' && input[i + 2] == 'r')
                {
                    if(input[i + 3] == ' '
                        || input[i + 3] == '\t')
                    {
                        //Sets the operation Code to 0,
                        //Function Code to 2,
                        //and Shift amount to 0.
                        operations[0] = 0;
                        operations[5] = 2;
                        operations[4] = 0;
                        input += 3;
                        opIded = 1;
                    }
                }
            }

            //sub and subi commands
            if (input[i] == 's')
            {
                if (input[i + 1] == 'u' && input[i + 2] == 'b')
                {
                    if(input[i + 3] == ' '
                        || input[i + 3] == '\t')
                    {
                        //Sets the operation Code to 0,
                        //Function Code to 34,
                        //and Shift amount to 0.
                        operations[0] = 0;
                        operations[5] = 34;
                        operations[4] = 0;
                        input += 3;
                        opIded = 1;
                    }
                    if ((input[i + 3] == 'i') && (input[i] == ' '
                                                  || input[i + 3] == '\t'))
                    {
                        operations[0] = 1;
                        operations[5] = 34;
                        operations[4] = 0;
                        input += 4;
                        opIded = 1;
                    }
                }
            }

            //and command
            if (input[i] == 'a')
            {
                if (input[i + 1] == 'n' && input[i + 2] == 'd')
                {
                    if(input[i + 3] == ' '
                        || input[i + 3] == '\t')
                    {
                        //Sets the operation Code to 0,
                        //Function Code to 32,
                        //and Shift amount to 0.
                        operations[0] = 0;
                        operations[5] = 36;
                        operations[4] = 0;
                        input += 3;
                        opIded = 1;
                    }
                }
            }
            //or command
            if (input[i] == 'o')
            {
                if (input[i + 1] == 'r')
                {
                    if(input[i + 2] == ' '
                        || input[i + 2] == '\t')
                    {
                        //Sets the operation Code to 0,
                        //Function Code to 37,
                        //and Shift amount to 0.
                        operations[0] = 0;
                        operations[5] = 37;
                        operations[4] = 0;
                        input += 2;
                        opIded = 1;
                    }
                }
            }
            //xor command
            if (input[i] == 'x')
            {
                if (input[i + 1] == 'o' && input[i + 2] == 'r')
                {
                    if(input[i + 3] == ' '
                        || input[i + 3] == '\t')
                    {
                        //Sets the operation Code to 0,
                        //Function Code to 38,
                        //and Shift amount to 0.
                        operations[0] = 0;
                        operations[5] = 38;
                        operations[4] = 0;
                        input += 3;
                        opIded = 1;
                    }
                }
            }

            //nor command
            if (input[i] == 'n')
            {
                if (input[i + 1] == 'o' && input[i + 2] == 'r')
                {
                    if(input[i + 3] == ' '
                        || input[i + 3] == '\t')
                    {
                        //Sets the operation Code to 0,
                        //Function Code to 39,
                        //and Shift amount to 0.
                        operations[0] = 0;
                        operations[5] = 39;
                        operations[4] = 0;
                        input += 3;
                        opIded = 1;
                    }
                }
            }
            //slt command
            if (input[i] == 's')
            {
                if (input[i + 1] == 'l' && input[i + 2] == 't')
                {
                    if(input[i + 3] == ' '
                        || input[i + 3] == '\t')
                    {
                        //Sets the operation Code to 0,
                        //Function Code to 32,
                        //and Shift amount to 0.
                        operations[0] = 0;
                        operations[5] = 42;
                        operations[4] = 0;
                        input += 3;
                        opIded = 1;
                    }
                }
            }
            //load word
            if (input[i] == 'l' && input[i + 1] == 'w' && (input[i + 2] == ' ' || input[i + 2] == '\t'))
            {
                operations[0] = 1;
                operations[3] = 0;
                operations[5] = 2;
                rs = 1;
                opIded = 1;
                i += 2;
            }
            //store word
            if (input[i] == 's' && input[i + 1] == 'w' && (input[i + 2] == ' ' || input[i + 2] == '\t'))
            {
                operations[0] = 1;
                operations[3] = 0;
                operations[5] = 3;
                rs = 1;
                opIded = 1;
                i += 2;
            }
            //syscall
            if (input[i] == 's' && input[i + 1] == 'y' && input[i + 2] == 's' &&
                input[i + 3] == 'c' && input[i + 4] == 'a' && input[i + 5] == 'l' &&
                input[i + 6] == 'l')
            {
                operations[0] = -1;
                operations[3] = 2;
                operations[5] = registers[2];
                break;
            }
            //For Load Address
            if (input[i] == 'l' && input[i + 1] == 'a'
                && (input[i + 2] == ' ' || input[i + 2] =='\t'))
            {
                operations[0] = 1;
                operations[3] = 0;
                operations[5] = 1;
                rs = 1;
                opIded = 1;
                i += 2;
            }
            
            if (!opIded && !labelIDed)
            {
                std::cout << "INVALID COMMAND- NO OPERATION OR LABEL"<< std::endl;
                Program.pop_back();
                --program_counter;
                break;
            }
            
        }
        //Tokenizes registers (starts with s0 registers)
        else{
            if (input[i] == '$' && input[i + 1] == 's')
            {
                switch(input[i + 2])
                {
                    case '0':
                        if (!rd)
                        {
                            operations[3] = 16;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 16;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 16;
                            rt = 1;
                        }
                        break;
                        
                    case '1':
                        if (!rd)
                        {
                            operations[3] = 17;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 17;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 17;
                            rt = 1;
                        }
                        break;
                        
                    case '2':
                        if (!rd)
                        {
                            operations[3] = 18;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 18;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 18;
                            rt = 1;
                        }
                        break;
                        
                    case '3':
                        if (!rd)
                        {
                            operations[3] = 19;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 19;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 19;
                            rt = 1;
                        }
                        break;
                        
                    case '4':
                        if (!rd)
                        {
                            operations[3] = 20;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 20;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 20;
                            rt = 1;
                        }
                        break;
                        
                    case '5':
                        if (!rd)
                        {
                            operations[3] = 21;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 21;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 21;
                            rt = 1;
                        }
                        break;
                  
                    case '6':
                        if (!rd)
                        {
                            operations[3] = 22;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 22;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 22;
                            rt = 1;
                        }
                        break;
                        
                    case '7':
                        if (!rd)
                        {
                            operations[3] = 23;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 23;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 23;
                            rt = 1;
                        }
                        break;
                }
                i += 2;
                continue;
            }
            
            if (input[i] == '$' && input[i + 1] == 't')
            {
                switch(input[i + 2])
                {
                    case '0':
                        if (!rd)
                        {
                            operations[3] = 8;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 8;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 8;
                            rt = 1;
                        }
                        break;
                        
                    case '1':
                        if (!rd)
                        {
                            operations[3] = 9;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 9;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 9;
                            rt = 1;
                        }
                        break;
                        
                    case '2':
                        if (!rd)
                        {
                            operations[3] = 10;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 10;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 10;
                            rt = 1;
                        }
                        break;
                        
                    case '3':
                        if (!rd)
                        {
                            operations[3] = 11;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 11;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 11;
                            rt = 1;
                        }
                        break;
                        
                    case '4':
                        if (!rd)
                        {
                            operations[3] = 12;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 12;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 12;
                            rt = 1;
                        }
                  break;
                  
                    case '5':
                        if (!rd)
                        {
                            operations[3] = 13;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 13;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 13;
                            rt = 1;
                        }
                        break;
                        
                    case '6':
                        if (!rd)
                        {
                            operations[3] = 14;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 14;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 14;
                            rt = 1;
                        }
                        break;
                        
                    case '7':
                        if (!rd)
                        {
                            operations[3] = 15;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 15;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 15;
                            rt = 1;
                        }
                        break;
                        
                    case '8':
                        if (!rd)
                        {
                            operations[3] = 24;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 24;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 24;
                            rt = 1;
                        }
                        break;
                        
                    case '9':
                        if (!rd)
                        {
                            operations[3] = 25;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 25;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 25;
                            rt = 1;
                        }
                        break;
                }
                i += 2;
                continue;
            }
            
            if (input[i] == '$' && input[i + 1] == 'v')
            {
                switch(input[i + 2])
                {
                    case '0':
                        if (!rd)
                        {
                            operations[3] = 2;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 2;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 2;
                            rt = 1;
                        }
                        break;
                        
                    case '1':
                        if (!rd)
                        {
                            operations[3] = 3;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 3;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 3;
                            rt = 1;
                        }
                        break;
                }
                i += 2;
                continue;
            }
            
            
            
            if (input[i] == '$' && input[i + 1] == 'a')
            {
                switch(input[i + 2])
                {
                    case '0':
                        if (!rd)
                        {
                            operations[3] = 4;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 4;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 4;
                            rt = 1;
                        }
                        break;
                        
                    case '1':
                        if (!rd)
                        {
                            operations[3] = 5;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 5;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 5;
                            rt = 1;
                        }
                        break;
                        
                    case '2':
                        if (!rd)
                        {
                            operations[3] = 6;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 6;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 6;
                            rt = 1;
                        }
                        break;
                        
                    case '3':
                        if (!rd)
                        {
                            operations[3] = 7;
                            rd = 1;
                        }
                        else if (!rs)
                        {
                            operations[1] = 7;
                            rs = 1;
                        }
                        else
                        {
                            operations[2] = 7;
                            rt = 1;
                        }
                        break;
                }
                i += 2;
                continue;
            }
            
            //Tokenizes Label Variables
            if (input[i] >= 65 && input[i] <= 90 && !prompt)
            {
                std::string  labelString;
                while (i < MAX_BUF)
                {
                    if (input[i] == ' ' || (input[i] < 48 && input[i] > 122))
                        break;
                    labelString += input[i];
                    ++i;
                }
                //std::cout << labelString << std::endl;
                //For labels in the text field
                for (int j = 0; j < Labels.size(); ++j)
                {
                    if (labelString == *Labels[j])
                    {
                        operations[2] = position[j];
                        rt = 1;
                        goto finishComp;
                        //break;
                    }
                }

                //Need to check labels in the Data Field as well
                //This is for la, lw, and sw operations
                for (int j = 0; j < DataLabels.size(); ++j)
                {
                    if (labelString == *DataLabels[j])
                    {
                        operations[2] = dpos[j];
                        rt = 1;
                        goto finishComp;
                        //break;
                    }
                }
                if (operations[0] == 2)
                {
                    if (outLabels.size() == 0)
                    {
                        outLabels.push_back(labelString);
                        outPos.push_back(program_counter);
                    }
                    else if(outLabels[outLabels.size() - 1] != labelString)
                    {
                        outLabels.push_back(labelString);
                        outPos.push_back(program_counter);
                    }
                    rt = 1;
                    execute = 0;
                    goto finishComp;
                }
                --program_counter;
                Program.pop_back();
                std::cout << "INVALID LABEL" << std::endl;
            }
            
        
//Tokenizes Numbers
            if (input[i] >= 48 && input[i] <= 57 && !rt)
            {
                int val = 0;
                int j = i;
                while (input[j] != ' ' || input[j] != '\t' ||
                       input[j] != '\0' || j < MAX_BUF || input[j] =='(')
                {
                    val *= 10;
                    val += input[j] - 48;
                    if (input[j - 1] == '-')
                        val *= -1;
                    j += 1;
                    if(input[j] < 48 || input[j] > 57)
                        break;
                }
                operations[2] = val;
                rt = 1;
                i += (j - i) - 1;
            }
          finishComp:
            if (!rs || !rt || !rd)
            {
                std::cout << "INVALID COMMAND- IMPROPER AMOUNT OF VARIABLES" << std::endl;
                std::cout << rd << ' ' << rs << ' ' << rt << std::endl;
                --program_counter;
                Program.pop_back();
                execute = 0;
                break;
            }
            if (input[i] == '\0' || (rs && rt && rd))
            {
                
                break;
            }
        }
        
    }
    ++program_counter;
}

void dataParse(char input[])
{
    std::string * inputString = new std::string;
    *(inputString) = input;
    bool labelIDed = 0;
    for (int i = 0; i < MAX_BUF; ++i)
    {
        if (input[i] == '.')
        {
            i += 4;
        }
        if (input[i] == 't' && input[i + 1] == 'e' && input[i + 2] =='x' && input[i + 3] == 't')
        {
            enterData = 0;
            break;
        }
        
        if (input[i] >= 65 && input[i] <= 90 && !prompt)
        {
            std::string * labelString = new std::string;
            while (i < MAX_BUF)
            {
                if (input[i] == ':')
                    break;
                *(labelString) += input[i];
                ++i;
            }
            //Makes sure the label isn't already used before pushing back label
            for(int j = 0; j < DataLabels.size(); ++j)
            {
                if (*labelString == *DataLabels[j])
                {
                    goto endDLcheck;
                }
            }
            DataLabels.push_back(labelString);
            dpos.push_back(data_position);
            labelIDed = 1;
            //break;
        }
      endDLcheck:
        if (input[i] == ' ')
            continue;
        if (input[i] == '"')
        {
            ++i;
            while(input[i] != '"')
            {
                Data.push_back(input[i]);
                ++data_position;
                ++i;
                if(input[i] == '\0')
                {
                    std::cout << "INVALID ENTRY, NO MATCHING QUOTATION FOUND" << std::endl;
                }
            }
            Data.push_back(0);
            ++data_position;
            EndPos.push_back(data_position);
            break;
            //std::cout << data_position << std::endl;
        }
    }
        
}

//Branching and Jump functions
void beq()
{
    //std::cout << registers[operations[3]] << ' ' << registers[operations[1]] << std::endl;
    if (registers[operations[3]] == registers[operations[1]])
    {
        //std::cout << registers[operations[3]] << ' ' << registers[operations[1]] << std::endl;
        execute = 0;
        branched = 1;
        return;
    }
    execute = 1;
    branched = 0;
}

void bne()
{
    if (registers[operations[3]] != registers[operations[1]])
    {
        execute = 0;
        branched = 1;
        return;
    }
    execute = 1;
    branched = 0;
}

void blt()
{
    if (registers[operations[3]] < registers[operations[1]])
    {
        execute = 0;
        branched = 1;
        
        return;
    }
    execute = 1;
    branched = 0;
}

void bgt()
{
    if (registers[operations[3]] > registers[operations[1]])
    {
        execute = 0;
        branched = 1;
        return;
    }
    execute = 1;
    branched = 0;
}

void bge()
{
    if (registers[operations[3]] >= registers[operations[1]])
    {
        execute = 0;
        branched = 1;
        return;
    }
    execute = 1;
    branched = 0;
}

void ble()
{
    if (registers[operations[3]] <= registers[operations[1]])
    {
        execute = 0;
        branched = 1;
        return;
        
    }
    execute = 1;
    branched = 0;
}

void jump()
{
    //If the Label is found(ie Label is found above the jump)
    int PC = program_counter;
    program_counter = operations[2] + 1;
    char input[MAX_BUF];
    //std::cout << PC << ' ' << program_counter;
    for (int i = program_counter; i <= PC; ++i)
    {
        if(branched)
            continue;
        //Set Second Time to 1 so Program doesn't grow
        secondTime = 1;
        std::string s = *(Program[i]);
        //std::cout << s << std::endl; 
        strcpy(input, s.c_str());
        tokenizerCommand(input);
        secondTime = 0;
        MIPS();
    }
}
#endif
