#ifndef GLOBALS_H
#define GLOBALS_H
#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <stack>


int MAX_BUF = 1024;

//booleans for checks
bool exitCase = 0;
bool secondTime = 0;
bool prompt = 0;
bool mode = 0;
bool enterData = 0;
bool branched = 0;
//Creates a register array for storing values
int registers[32];
int LO = 0;
int HI = 0;

//Creates an array for operations, Similar to how our computers use binary
//strings to call functions
int operations[6];
//|  0   |1 |2 |3 | 4  | 5  |
//|opCode|rs|rt|rd|shft|func|

//array for storing the Program in Immediate mode
std::vector<std::string *> Program;

//Vectors for storing Labels and Label positions
std::vector<std::string *> Labels;
std::vector<int> position;

//Vectors for storing Data Labels, Data Position, and Data.
std::vector<std::string *>DataLabels;
std::vector<int> dpos;
std::vector<int> EndPos;
std::vector<int> Data;

//Stack for outstanding labels
std::vector<std::string>outLabels;
std::vector<int> outPos;

int program_counter = 0;
int data_position = 0;
bool execute = 1;


#endif
