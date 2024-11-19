#include <stdio.h>
#include <stdlib.h>

typedef struct Instruct{
    int opcode;
    int operand;
}instruct;


int main(int argc, char const *argv[]){

    const int limit = 255;
    const char* arquivo = "nome_do_arquivo.txt";

    FILE* Program = fopen(arquivo,"r");

    if(Program == NULL){
        perror("Arquivo nao encontrado");
        return 1;
    }
    

    //inicialização do programa na memória
    instruct program[limit], instruction;

    int opcode, operand, pc=0,acc=0,mem[limit];

    for (int i = 0; i < limit; i++)
    {
        program[i].opcode = 0;
        program[i].operand = 0;
        mem[i] = 0;
    }
    
    int cont_intrucoes = 0;
    while (fscanf(Program, "%x %x", &program[cont_intrucoes].opcode, &program[cont_intrucoes].operand))
    {
        cont_intrucoes++;
        if (cont_intrucoes >= limit) {
            fprintf(stderr, "Programa excedeu o limite de instruções.\n");
            return 1;
        }
    }
    

    while(pc<cont_intrucoes){
        instruction = program[pc];
        opcode = instruction.opcode;
        operand = instruction.operand;
        pc++;

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