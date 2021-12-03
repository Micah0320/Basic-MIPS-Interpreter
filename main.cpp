#include "util.h"
#include <fstream>

void MIPS();
void Prompt();
void printData();
void printLabels();
void printText();
void printReg();
//Various Print Functions for debuging.
void Welcome()
{
    std::cout << "Welcome to Micah's Mips, currently in beta." << std::endl;
    std::cout << "Currently using: immediate mode. Some functions will be disabled." << std::endl;
    std::cout << "-Labels must be capitalized and must not have SPIM after\n-Type Data to input Data\n-Type Batch to run the batch.s file\n-You can enter an empty string to end the program" <<std::endl;

    std::cout << '\n' << "What mode would you like?\n0 - Immediate\n1 - Batch\nMode: ";
    std::cin >> mode;
    prompt = 1;
}

void Goodbye()
{
    char option;
    std::cout << "Would you like to execute the program again? y/n: ";
    std::cin  >> option;
    if (option == 'y')
    {
        secondTime = 1;
        program_counter = 0;
        char input[MAX_BUF];
        for (int i = 0; i < Program.size(); ++i)
        {
             std::string s = *(Program[i]); 
             strcpy(input, s.c_str());
             tokenizerCommand(input);
             MIPS();
        }
    }
    std::cout << "Would you like to save the program? y/n: ";
    std::cin  >> option;
    if (option == 'y')
    {
        std::ofstream batchFile("batch.s");
        if (batchFile.is_open())
        {
            batchFile << "\t.text\n";
            batchFile << "\t.globl main\n";
            batchFile << "main: \n";
            for (int i = 0; i < Program.size(); ++i)
            {
                batchFile << '\t' <<*(Program[i]) << '\n';
            }
            batchFile <<"\n\t.data\n";
            for (int i = 0; i < DataLabels.size(); ++i)
            {
                batchFile << '\t' <<*(DataLabels[i]) << ':' << "\t.word ";
                for (int j = dpos[i]; j < EndPos[i]; ++j)
                {
                    batchFile << Data[j];
                    if (j != EndPos[i] - 1)
                        batchFile << ',';
                }
                batchFile << '\n';
            }
        }
        
    }
    std::cout << "END" << std::endl;
}
void Input(char input[]);
void MIPS()
{
    if (operations[0] == -2)
    {
        
        switch(operations[5])
        {
            case 0:
                printText();
                break;
            case 1:
                printLabels();
                break;
            case 2:
                printReg();
                break;
            case 3:
                printData();
                break;
        }
        
    }
    if (operations[0] == -1)
            syscall();
        if(operations[0] == 0 && execute)
        {
            //r-format Instructions
            switch(operations[5])
            {
                case 0:
                    sll();
                    break;
                case 2:
                    slr();
                    break;
                case 18:
                    mflo();
                    break;
                case 19:
                    mfhi();
                    break;
                case 26:
                    mult();
                    break;
                case 28:
                    div();
                    break;
                case 32:
                    add();
                    break;
                case 34:
                    sub();
                    break;
                case 36:
                    andF();
                    break;
                case 37:
                    orF();
                    break;
                case 38:
                    xorF();
                    break;
                case 39:
                    nor();
                    break;
                case 42:
                    slt();
                    break;
            }
        }

        if(operations[0] == 1 && execute)
        {
            switch (operations[5])
            {
            //i-format instructions
                case 1:
                    la();
                    break;
                case 2:
                    lw();
                    break;
                case 3:
                    sw();
                    break;
                case 32:
                    addi();
                    break;
                case 34:
                    subi();
                    break;
                case 48:
                    load_immediate();
                    break;
            }
        }
        if (operations[0] == 2 && (execute || !branched))
        {
            switch (operations[5])
            {
                case 0:
                    jump();
                    break;
                case 1:
                    beq();
                    break;
                case 2:
                    bne();
                    break;
                case 3:
                    blt();
                    break;
                case 4:
                    bgt();
                    break;
                case 5:
                    ble();
                    break;
                case 6:
                    bge();
                    break;
                    
            }
        }
}

int main()
{
    char input[MAX_BUF];
    init();
    Welcome();
    if(!mode)
    {
        while (1)
        {
            
            Input(input);
            
            // if input is "" break the while loop
            if (*(input) == '\0' && !(prompt))
                break;
            if (!enterData)
            {
                tokenizerCommand(input);
                MIPS();
            }
            else
            {
                dataParse(input);
            }
            
            //printReg();
            if (exitCase && !(prompt))
                break;
            prompt = 0;
            
        }
    }
    else
    {
        std::ifstream batchFile("batch.s");
        if (batchFile.is_open())
        {
            std::string s;
            int periods = 0;
            bool Dentry = 0;
            char input[MAX_BUF];
            while(getline(batchFile, s))
            {
                if (s == "\t.text" || s == "\t.globl main")
                    continue;
                if (s == "\t.data")
                {
                    Dentry = 1;
                    continue;
                }
                if (!Dentry)
                {
                    std::string* t = new std::string;
                    *(t) = s;
                    Program.push_back(t);
                    //strcpy(input, s.c_str());
                    //tokenizerCommand(input);
                }
                
                else
                {
                    strcpy(input, s.c_str());
                    dataParse(input);
                }
                
            }
            batchFile.close();
            for (int i = 0; i < Program.size(); ++i)
            {
                s = *(Program[i]);
                //std::cout << s << std::endl;
                strcpy(input, s.c_str());
                secondTime = 1;
                tokenizerCommand(input);
                
                MIPS();
            }
        }
    }
    //printProgram();
    Goodbye();
    
}

void printReg()
{
    for(int i = 0; i <  32; ++i)
    {
        std::cout << '$' <<  i << ": " << registers[i] << std::endl;
    }
    prompt = 1;
}

void printLabels()
{
    for (int i = 0; i < Labels.size(); ++i)
    {
        std::cout << position[i] << ' ' << *(Labels[i]) << std::endl;
    }
    prompt = 1;
}

void printData()
{
    //std::cout << "TO DO" << std::endl;
    std::cout << "You have " << DataLabels.size() << " data labels." << std::endl;
    for (int i = 0; i < DataLabels.size(); ++i)
    {
        std::cout << *(DataLabels[i]) << ' ';
        std::cout << dpos[i] << ' ';
        //Print out data
        for(int j = dpos[i]; j < EndPos[i]; ++j)
        {
            std::cout << char(Data[j]);
        }
        std::cout << std::endl;
    }
}

void printText()
{
    for (int i = 0; i < Program.size(); ++i)
    {
        std::cout << *(Program[i]) << std::endl;
    }
}

void printOps()
{
    for (int i = 0; i < 6; ++i)
    {
        std::cout << operations[i] << ' ';
    }
    std::cout << std::endl;
}



void Input(char input[])
{
    if (!prompt)
    {
        if (!enterData)
            std::cout << "Text ";
        else
            std::cout << "Data ";
        std::cout << ">>> ";
    }
// read string from keyboard and put into input array of characters
        std::cin.getline(input, MAX_BUF);
        //if (std::cin.eof()) break;
        if (std::cin.fail() || std::cin.bad())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
        }
    
        

}

