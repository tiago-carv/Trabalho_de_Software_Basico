#include <stdio.h>
#include <stdlib.h>

typedef struct Instruct{
    int opcode;
    int operand;
}instruct;

typedef unsigned char byte;

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

    byte opcode, operand, pc=0,acc=0,stat=0,mem[limit];

    for (int i = 0; i < limit; i++)
    {
        program[i].opcode = 0;
        program[i].operand = 0;
    }
    
    int cont_intrucoes = 0;
    while ((fread(&program[cont_intrucoes],sizeof(char),1,arquivo)) != 0)
    {
        fread(&program[cont_intrucoes],sizeof(char),1,arquivo);
        cont_intrucoes++;
    }
    

    while( program[pc].opcode != 0x13){
        instruction = program[pc];
        opcode = instruction.opcode;
        operand = instruction.operand;
        pc++;

        switch (opcode)
        {
        case 0x00:  //LOAD
            acc = mem[operand];
            break;
        case 0x01:  //LOAD
            acc = operand;
            break;
        case 0x02:  //STORE
            mem[operand] = acc;
            break;
        case 0x03:  //ADD
            acc = acc + mem[operand];
            break;
        case 0x04:  //SUB
            acc = acc - mem[operand];
            break;
        case 0x05:  //MUL
            acc = acc * mem[operand];
            break;
        case 0x06:  //DIV
            acc = acc / mem[operand];
            break;
        case 0x07:  //INC
            acc++;
            break;
        case 0x08:  //DEC
            acc--;
            break;
        case 0x09:  //AND
            acc = acc & mem[operand];
            break;
        case 0x0A:  //OR
            acc = acc | mem[operand];
            break;
        case 0x0B:  //NOT
            acc = ~acc;
            break;
        case 0x0C:  //JMP
            pc = operand;
            break;
        case 0x0D:  //JZ
            if(acc == 0) pc = operand;
            break;
        case 0x0E:  //JNZ
            if(acc != 0) pc = operand;
            break;
        case 0x0F:  //JG
            if(acc > 0) pc = operand;
            break;
        case 0x10:  //JL
            if(acc < 0) pc = operand;
            break;
        case 0x11:  //JGE
            if(acc >= 0) pc = operand;
            break;
        case 0x12:  //JLE
            if(acc <= 0) pc = operand;
            break;
        default:
            perror("Operação inesistente!");
            return 1;
            break;
        }
    }    
    if(acc == 0) stat = 0 ;
    printf("acc: %d\n",acc);
    
    return 0;
}