#include <string>
#include "global.h"

// store the file content in buffer for the solver to read them one by one
string problemBuffer[PROBLEM_BUFFER_LEN];

// a dedicated thread hold the program for reading content from files
void ReadController();

// each file read by a thread 
void ReadThread(FILE filename);