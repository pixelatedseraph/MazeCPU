#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdarg.h>

/*
Copyright 
    Mazeed A. (2026)
*/

//Functions    -> snake_case
//Types        -> PascalCase
//Struct Fields-> PascalCase
//Variables    -> camelCase
//Fun-Macros   -> PascalCase

#define let __auto_type

typedef uint8_t  Byte;
typedef uint16_t Word;

#define KiloByte(n) (n) * (1024)

const uint32_t MaximumMemoryLimit = KiloByte(64);

typedef struct PhysicalMemory {
    uint32_t MaximumMemoryLimit;
    Byte Data[MaximumMemoryLimit]; 
}PhysicalMemory;

PhysicalMemory new_physical_memory(){
    return (PhysicalMemory){.MaximumMemoryLimit = MaximumMemoryLimit};
}

static inline void memory_initialize(PhysicalMemory* memory){
    memset(memory->Data,0,sizeof (Byte) * memory->MaximumMemoryLimit);
}

/* ProcessorStatus Flags */
typedef struct{
    Byte Carry     : 1;
    Byte Zero      : 1;
    Byte Interrupt : 1;
    Byte Decimal   : 1;
    Byte Break     : 1;
    Byte Overflow  : 1;
    Byte Negative  : 1;
}CPUStatus;

typedef struct{
    Byte A;
    Byte X;
    Byte Y;
}CPURegister;

typedef struct{
    Word ProgramCounter;
    Word StackPointer;

    CPURegister* Registers; 
    CPUStatus* ProcesserStatus;
}CPU;

CPU new_cpu(){
    return (CPU){};
}

void cpu_reset(CPU* cpuInstance,PhysicalMemory* memory){
    cpuInstance->ProgramCounter = 0xFFFC;
    cpuInstance->StackPointer   = 0x0100;

    let status = cpuInstance->ProcesserStatus;
    status->Carry = status->Zero = status->Interrupt = status->Decimal = 0;
    status->Break = status->Overflow = status->Negative = 0;

    let register = cpuInstance->Registers;
    register->A = register->X = register->Y = 0;

    memory_initialize(memory);
}

void cpu_fetch(){

}

void cpu_execute(CPU* cpuInstance,PhysicalMemory* memory,uint64_t cycles){
    while(cycles > 0){

        cycles--;
    }
}


int main(){
    let memory =  new_physical_memory();
    let cpu = new_cpu();

    cpu_reset(&cpu,&memory);

    cpu_execute(&cpu,&memory,2);

    return 0;
}