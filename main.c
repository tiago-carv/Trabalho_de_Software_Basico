#include <stdio.h>
#include <stdlib.h>

typedef signed char byte;
typedef struct Instruct{
    byte opcode;
    byte operand;
}instruct;

void check_carry_and_overflow(byte a, byte b, int op, byte* status);

int main(int argc, char const *argv[]){

    const int limit = 255;
    const char* archive_name = argv[argc-1];

    FILE* Program = fopen(archive_name,"rb");

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
    byte digit = 0;
    while ((fread(&digit,1,1,Program)) != 0)
    {
        program[cont_intrucoes].opcode = digit;
        if(fread(&digit,1,1,Program) !=0){
            program[cont_intrucoes].operand = digit;
        }else{
            perror("Número de operando insuficiente");
            return 1;
        }
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
            check_carry_and_overflow(acc,mem[operand],1,&stat);
            acc = acc + mem[operand];
            break;
        case 0x04:  //SUB
            check_carry_and_overflow(acc,mem[operand],-1,&stat);
            acc = acc - mem[operand];
            break;
        case 0x05:  //MUL
            check_carry_and_overflow(acc,mem[operand],2,&stat);
            acc = acc * mem[operand];
            break;
        case 0x06:  //DIV
            acc = acc / mem[operand];
            break;
        case 0x07:  //INC
            check_carry_and_overflow(acc,1,1,&stat);
            acc++;
            break;
        case 0x08:  //DEC
            check_carry_and_overflow(acc,-1,-1,&stat);
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
            if(acc == 0) {
                pc = operand;
            }else{
                pc++;
            }
            break;
        case 0x0E:  //JNZ
            if(acc != 0) {
                pc = operand;
            }else{
                pc++;
            }
            break;
        case 0x0F:  //JG
            if(acc > 0) {
                pc = operand;
            }else{
                pc++;
            }
            break;
        case 0x10:  //JL
            if(acc < 0) {
                pc = operand;
            }else{
                pc++;
            }
            break;
        case 0x11:  //JGE
            if(acc >= 0) {
                pc = operand;
            }else{
                pc++;
            }
            break;
        case 0x12:  //JLE
            if(acc <= 0) {
                pc = operand;
            }else{
                pc++;
            }
            break;
        default:
            perror("Operação inesistente!");
            return 1;
            break;
        }
    }    
    if(acc == 0) stat = stat | 1 ;
    printf("acc: %d\n stat: %d\n",acc,stat);
    
    return 0;
}

void check_carry_and_overflow(byte a, byte b, int op, byte* status) {
    byte result;
    if (op == 2){
        result = (int)a * b;
    }else{
        result = a + b * op;
    }
    
    int carry = (a > 127 - b) ||(a < -128 - b); // Verifica se houve carry-out
    int overflow = ((a > 0 && b > 0 && result < 0) || (a < 0 && b < 0 && result > 0)) != 0; // Detecta overflow

    if (op != 2) *status |= carry;
    *status |= overflow;
}