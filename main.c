#include <stdio.h>

typedef struct Instruct{
    int opcode;
    int operand;
}instruct;


int main(int argc, char const *argv[]){

    const int limit = 255;
    const char* arquivo = "nome_do_arquivo.txt";

    FILE* Program = fopen(arquivo,"r");

    //inicialização do programa na memória
    instruct program[limit], instruction;

    int opcode, operand, pc=0,acc=0,mem[limit];

    while(pc<limit){
        instruction = program[pc];
        opcode = instruction.opcode;
        operand = instruction.operand;

        switch (opcode)
        {
        case 0x00:
            /* code */
            break;
        
        default:
            break;
        }
    }
    
    return 0;
}