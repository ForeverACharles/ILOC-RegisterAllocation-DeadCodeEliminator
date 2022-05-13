/*
 *********************************************
 *  415 Compilers                            *
 *  Spring 2021                              *
 *  Students                                 *
 *********************************************
 */


#include "Instr.h"
#include <stdio.h>

#ifndef INSTR_UTILS_H
#define INSTR_UTILS_H

void PrintInstruction(FILE * outfile, Instruction * instr);
void PrintInstructionList(FILE * outfile, Instruction * instr);
Instruction *ReadInstruction(FILE * infile);
Instruction *ReadInstructionList(FILE * infile);
Instruction *LastInstruction(Instruction * instr);
void DestroyInstructionList(Instruction * instr);

Instruction* ElimateDeadCode(Instruction * instr);
int* DetermineDestination(Instruction* instr);
Instruction* GetNextUse(Instruction* ptr, int dest1, int dest2);

#endif
