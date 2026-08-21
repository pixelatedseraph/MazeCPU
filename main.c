#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdarg.h>

/*
 *  main.c 
 *
 *  Entry point for the MazeCPU 6502 emulator
 *
 * Author: Mazeed A.
 * SPDX-License-Identifier: AGPLv3
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
    Byte Data[]; 
}PhysicalMemory;

static inline PhysicalMemory* new_physical_memory(){
    PhysicalMemory* memory = malloc(sizeof(PhysicalMemory) + MaximumMemoryLimit * sizeof(Byte));
    memory->MaximumMemoryLimit = MaximumMemoryLimit;
    return memory;
}

static inline void delete_physical_memory(PhysicalMemory** memory){
    free(*memory);
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

static inline CPUStatus new_cpu_status(){
    return (CPUStatus){};
}

typedef struct{
    Byte A;
    Byte X;
    Byte Y;
}CPURegister;

static inline CPURegister new_cpu_register(){
    return (CPURegister){};
}

typedef struct{
    Word ProgramCounter;
    Word StackPointer;

    CPURegister Registers; 
    CPUStatus   ProcesserStatus;
}CPU;

typedef enum {
    LDAImmediate  //Load Accumalator- Immediate Addressing Mode
}OpCodeIdentifier;


static const Byte CPUOpCodes [] = {
    [LDAImmediate] = 0xA9,
};

CPU new_cpu(){
    let cpu = (CPU){.ProcesserStatus = new_cpu_status(), .Registers = new_cpu_register()};
    return cpu;
}

void cpu_reset(CPU* cpuInstance,PhysicalMemory* memory){
    cpuInstance->ProgramCounter = 0xFFFC;
    cpuInstance->StackPointer   = 0x0100;

    let status = cpuInstance->ProcesserStatus;
    status.Carry = status.Zero = status.Interrupt = status.Decimal = 0;
    status.Break = status.Overflow = status.Negative = 0;

    let registers = cpuInstance->Registers;
    registers.A = registers.X = registers.Y = 0;

    memory_initialize(memory);
}

Byte cpu_fetch_byte(CPU* cpuInstance,PhysicalMemory* memory){
    let data = memory->Data[cpuInstance->ProgramCounter++];
    return data;
}

void cpu_execute(CPU* cpuInstance,PhysicalMemory* memory,uint64_t cycles){
    while(cycles > 0){
        let instruction = cpu_fetch_byte(cpuInstance,memory);
        
        switch(instruction){
            case CPUOpCodes[LDAImmediate]: /* Takes two clock cycles*/
                let value = cpu_fetch_byte(cpuInstance,memory);

                let regA = cpuInstance->Registers.A;
                regA = value;

                cpuInstance->ProcesserStatus.Zero = (regA == 0);
                cpuInstance->ProcesserStatus.Negative = (regA & 0b10000000) > 0;
            default:
                break;
        }

        cycles--;
    }
}


int main(void){
    [[gnu::cleanup(delete_physical_memory)]] let memory =  new_physical_memory();
    let cpu = new_cpu();

    cpu_reset(&cpu,memory);

    cpu_execute(&cpu,memory,2);

    return 0;
}