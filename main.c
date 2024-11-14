#include <stdio.h>

typedef struct instruct{
    int opcode;
    int operand;
}instruct;


int main(int argc, char const *argv[]){

    //inicialização do programa na memória
    instruct program[10];

    instruct instruction;
    int opcode,operand,pc=0;

    for(;;){
        instruction = program[pc];
        opcode = instruction.opcode;
        operand = instruction.operand;
    }
    
    return 0;
}